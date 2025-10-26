#include <iostream>
#include <optional>
#include <cmath>
#include <limits>

#include "Math.h"
#include "TileBounds.h"
#include "Collision.h"

// ----- Helper Function -----

Line define2DLine(const std::pair<sf::Vector3f, sf::Vector3f>& feetLine)
{
    Line l;
    l.p1 = sf::Vector2f(feetLine.first.x, feetLine.first.z);  // project first foot to XZ plane
    l.p2 = sf::Vector2f(feetLine.second.x, feetLine.second.z); // project second foot to XZ plane
    return l;
}

sf::FloatRect getTileTopBounds(const CubeTile& tile)
{
    float x = tile.m_gridCoords.x;
    float z = tile.m_gridCoords.z;

    return sf::FloatRect(x, z, 1.f, 1.f);
}

// ----- Collision Detection -----

// Check between 2 2D lines
bool Collision::LineLine(const Line& l1, const Line& l2)
{
    float denominator = (l2.p2.y - l2.p1.y) * (l1.p2.x - l1.p1.x) - 
        (l2.p2.x - l2.p1.x) * (l1.p2.y - l1.p1.y);

    // Don't divide by 0 dummy
    if (denominator == 0)
        return false;

    float uA = ((l2.p2.x - l2.p1.x) * (l1.p1.y - l2.p1.y) - 
            (l2.p2.y - l2.p1.y) * (l1.p1.x - l2.p1.x)) / denominator;

    float uB = ((l1.p2.x - l1.p1.x) * (l1.p1.y - l2.p1.y) - 
            (l1.p2.y - l1.p1.y) * (l1.p1.x - l2.p1.x)) / denominator;

    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
        return true;
    return false;
}

bool Collision::LineRect(const Line& line, const sf::FloatRect& rect)
{
    Line leftEdge   = { sf::Vector2f(rect.left, rect.top), sf::Vector2f(rect.left, rect.top + rect.height) };
    Line rightEdge  = { sf::Vector2f(rect.left + rect.width, rect.top), sf::Vector2f(rect.left + rect.width, rect.top + rect.height) };
    Line topEdge    = { sf::Vector2f(rect.left, rect.top), sf::Vector2f(rect.left + rect.width, rect.top) };
    Line bottomEdge = { sf::Vector2f(rect.left, rect.top + rect.height), sf::Vector2f(rect.left + rect.width, rect.top + rect.height) };

    if (LineLine(line, leftEdge) ||
        LineLine(line, rightEdge) ||
        LineLine(line, topEdge) ||
        LineLine(line, bottomEdge))
    {
        return true;
    }

    bool p1Inside =
        (line.p1.x >= rect.left && line.p1.x <= rect.left + rect.width &&
         line.p1.y >= rect.top && line.p1.y <= rect.top + rect.height);

    bool p2Inside =
        (line.p2.x >= rect.left && line.p2.x <= rect.left + rect.width &&
         line.p2.y >= rect.top && line.p2.y <= rect.top + rect.height);

    if (p1Inside && p2Inside)
        return true;

    return false;
}

bool Collision::LineHitsGrid(const std::pair<sf::Vector3f, sf::Vector3f>& feetLine, const sf::Vector3i& gridPos)
{
    // Project the player's feet line onto XZ plane
    Line line = define2DLine(feetLine);

    // Represent the grid cell as a 1x1 rectangle on XZ
    sf::FloatRect gridRect(
        static_cast<float>(gridPos.x),
        static_cast<float>(gridPos.z),
        1.f, 1.f
    );

    if (feetLine.first.y < -1.f)
        return false;

    // Check if the line crosses or ends inside that grid cell
    return Collision::LineRect(line, gridRect);
}

bool Collision::NearTiles(const sf::Vector3f& obj1, const sf::Vector3f& obj2, const float tolerance)
{
    return std::abs(obj1.x - obj2.x) <= tolerance && std::abs(obj1.z - obj2.z) <= tolerance;
}

bool Collision::TileUnder(const sf::Vector3f& obj, const std::vector<CubeTile*>& tiles)
{
    const float tolerance = 0.5f;

    if (obj.y < 0)
        return false;

    for (auto* t : tiles)
    {
        if (!t->m_tileId)
            continue;

        float dx = obj.x - t->m_gridCoords.x;
        float dz = obj.z - t->m_gridCoords.z;

        bool horizontallyAbove = (std::abs(dx) < tolerance && std::abs(dz) < tolerance);

        if (horizontallyAbove)
            return true;
    }

    return false;
}

// ----- Resolve -----

void Collision::Resolve(Player& p, const std::vector<CubeTile*>& tiles)
{
    float maxTopY = -std::numeric_limits<float>::infinity();
    bool collided = false;
    float buffer = 0.1f; // small buffer to prevent sinking
    float snapDist = 0.1f;

    for (auto* t : tiles)
    {
        if (!t->m_tileId) continue;

        float topY = t->m_gridCoords.y + t->m_logicalHeight;
        float distToTop = topY - p.m_gridPos.y;

        // Player is falling and feet are below tile top + buffer
        if (distToTop > -buffer && distToTop < snapDist && p.m_vel.y <= 0)
        {
            if (topY > maxTopY)
            {
                maxTopY = topY;
                collided = true;
            }
        }
    }

    if (collided)
    {
        p.m_gridPos.y = maxTopY;
        p.m_vel.y = 0.f;
        p.isJumping = false;
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
            if (LineRect(define2DLine(p.GetFeetLine()), getTileTopBounds(*t)))
                collidingTiles.push_back(t);
        }
    }
    return collidingTiles;
}
