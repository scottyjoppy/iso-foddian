#include <iostream>
#include <optional>
#include <cmath>
#include <limits>

#include "Math.h"
#include "TileBounds.h"
#include "Collision.h"

#define DISTANCE 1.5

// ----- Math Helpers -----

static float cross(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return a.x * b.y - a.y * b.x;
}

static float dot(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return a.x * b.x + a.y * b.y;
}

// ----- Helper Functions -----

Line createFeetLine(sf::FloatRect box)
{
    sf::Vector2f leftFoot(box.left, box.top + box.height);
    sf::Vector2f rightFoot(box.left + box.width, box.top + box.height);

    return { leftFoot, rightFoot };
}

Polygon createPolygon(const TileBounds& bounds)
{
    return bounds.GetVertices();
}

std::optional<sf::Vector2f> segmentIntersection(const Line& l1, const Line& l2, float eps = 1e-6f)
{
    sf::Vector2f p = l1.p1;
    sf::Vector2f r = { l1.p2.x - l1.p1.x, l1.p2.y - l1.p1.y}; 

    sf::Vector2f q = l2.p1;
    sf::Vector2f s = { l2.p2.x - l2.p1.x, l2.p2.y - l2.p1.y}; 

    float rxs = cross(r, s);
    sf::Vector2f q_p = { q.x - p.x, q.y - p.y };

    if (std::fabs(rxs) < eps)
    {
        if (std::fabs(cross(q_p, r)) < eps)
        {
            float rlen2 = dot(r, r);
            if (rlen2 < eps)
            {
                float slen2 = dot(s, s);
                if (slen2 < eps) return std::nullopt;
                float u = dot({p.x - q.x, p.y - q.y}, s) / slen2;
                if (u >= -eps && u <= 1.0f + eps) return p;
                return std::nullopt;
            }

            float t0 = dot(q_p, r) / rlen2;
            float t1 = dot({ q.x + s.x - p.x, q.y + s.y - p.y }, r) / rlen2;

            if (t0 > t1) std::swap(t0, t1);

            float tmin = std::max(0.0f, t0);
            float tmax = std::min(1.0f, t1);

            if (tmin <= tmax + eps)
            {
                sf::Vector2f intersection = { p.x + r.x * tmin, p.y + r.y * tmin };
                return intersection;
            }
            return std::nullopt;
        }
        return std::nullopt;
    }

    float t = cross(q_p, s) / rxs;
    float u = cross(q_p, r) / rxs;

    if (t >= -eps && t <= 1.0f + eps && u >= -eps && u <= 1.0f + eps)
    {
        sf::Vector2f intersection = { p.x + r.x * t, p.y + r.y * t };
        return intersection;
    }
    return std::nullopt;
}


bool pointInPolygon(const sf::Vector2f& point, const Polygon& poly)
{
    size_t n = poly.size();
    for (size_t i = 0; i < n; i++)
    {
        sf::Vector2f a = poly[i];
        sf::Vector2f b = poly[(i + 1) % n];
        sf::Vector2f edge = b - a;
        sf::Vector2f toPoint = point - a;
        if (cross(edge, toPoint) < 0) return false;
    }

    return true;
}

// ----- Collision Detection -----

bool Collision::LinePolygon(const Line& line, const Polygon& poly)
{
    if (poly.empty()) return false;

    size_t n = poly.size();
    for (size_t i = 0; i < n; i++)
    {
        Line edge{ poly[i], poly[(i + 1) % n] };
        if (segmentIntersection(line, edge).has_value())
            return true;
    }

    if (pointInPolygon(line.p1, poly) || pointInPolygon(line.p2, poly))
        return true;

    return false;
}

bool Collision::NearTiles(const sf::Vector3f& obj1, const sf::Vector3f& obj2)
{
    return std::abs(obj1.x - obj2.x) <= DISTANCE && std::abs(obj1.z - obj2.z) <= DISTANCE;
}

bool Collision::AABB(const sf::Vector3f& playerPos, float playerSize, const sf::Vector3i& tilePos, float tileSize = 1.0f)
{
    float halfSize = playerSize / 2.0f;

    return (playerPos.x + halfSize > tilePos.x &&
            playerPos.x - halfSize < tilePos.x + tileSize &&
            playerPos.z + halfSize > tilePos.z &&
            playerPos.z - halfSize < tilePos.z + tileSize);
}

// ----- Resolve -----

void Collision::Resolve(Player& p, const std::vector<CubeTile*>& tiles)
{
    for (auto* t : tiles)
    {
        if (t->m_tileId)
        {
            float topY = t->m_gridCoords.y + t->m_logicalHeight;

            if (p.m_gridPos.y < topY && p.m_vel.y < 0.f)
            {
                p.m_gridPos.y = topY;
                p.m_vel.y = 0.f;
                p.isJumping = false;

                break;
            }
        }
    }
}

// ----- Wrapper Function -----
std::vector<CubeTile*> Collision::BroadPhase(std::vector<CubeTile*>& allTiles, Player& p)
{
    std::vector<CubeTile*> collidingTiles;

    for (auto& t : allTiles)
    {
        if (!t->m_tileId) continue;

        sf::Vector3f tilePos(t->m_gridCoords.x, t->m_gridCoords.y, t->m_gridCoords.z);
        
        if (NearTiles(p.m_gridPos, tilePos))
        {
            float tileTop = t->m_gridCoords.y + t->m_logicalHeight;
            float tileBottom = t->m_gridCoords.y;

            if (p.m_gridPos.y >= tileBottom - 0.2f && 
                    p.m_gridPos.y <= tileTop + 1.0f &&
                    p.m_vel.y < 0.f)
            {
                if (AABB(p.m_gridPos, 0.6f, t->m_gridCoords))
                    collidingTiles.push_back(t);
            }
        }
    }
    return collidingTiles;
}
