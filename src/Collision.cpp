#include <math.h>
#include <iostream>

#include "Math.h"
#include "Collision.h"

//-----SAT Utility Functions-----

std::vector<sf::Vector2f> getNormals(const std::vector<sf::Vector2f>& poly)
{
    std::vector<sf::Vector2f> normals;
    int N = poly.size();
    for (int i = 0; i < N; i++)
    {
        sf::Vector2f p1 = poly[i];
        sf::Vector2f p2 = poly[(i + 1) % N];
        sf::Vector2f edge = p2 - p1;
        normals.push_back(sf::Vector2f(-edge.y, edge.x));
    }
    return normals;
}

void projectPolygon(const std::vector<sf::Vector2f>& poly, const sf::Vector2f& axis, float& min, float& max)
{
    min = max = poly[0].x * axis.x + poly[0].y * axis.y;
    for (size_t i = 1; i < poly.size(); i++)
    {
        float proj = poly[i].x * axis.x + poly[i].y * axis.y;
        if (proj < min) min = proj;
        if (proj > min) max = proj;
    }
}

bool overlap(float minA, float maxA, float minB, float maxB)
{
    return !(maxA < minB || maxB < minA);
}

bool polygonsIntersect(const std::vector<sf::Vector2f>& polyA, const std::vector<sf::Vector2f>& polyB)
{
    auto axesA = getNormals(polyA);
    auto axesB = getNormals(polyB);

    for (auto& axis : axesA)
    {
        float minA, maxA, minB, maxB;
        projectPolygon(polyA, axis, minA, maxA);
        projectPolygon(polyB, axis, minB, maxB);
        if (!overlap(minA, maxA, minB, maxB)) return false;
    }

    for (auto& axis : axesB)
    {
        float minA, maxA, minB, maxB;
        projectPolygon(polyA, axis, minA, maxA);
        projectPolygon(polyB, axis, minB, maxB);
        if (!overlap(minA, maxA, minB, maxB)) return false;
    }

    return true;
}

std::vector<sf::Vector2f> RectangleShapeToPoly(const sf::RectangleShape& rect)
{
    sf::Vector2f size = rect.getSize();
    std::vector<sf::Vector2f> poly;
    poly.push_back(rect.getTransform().transformPoint(sf::Vector2f(0.f, 0.f)));
    poly.push_back(rect.getTransform().transformPoint(sf::Vector2f(size.x, 0.f)));
    poly.push_back(rect.getTransform().transformPoint(sf::Vector2f(size.x, size.y)));
    poly.push_back(rect.getTransform().transformPoint(sf::Vector2f(0.f, size.y)));
    return poly;
}

//-----Utility Functions-----

std::vector<const CubeTile*> Collision::TilesUnderPlayer(const sf::RectangleShape& playerRect, const std::vector<CubeTile*>& tiles)
{
    std::vector<const CubeTile*> result;
    auto playerBottom = PlayerBottomPoints(playerRect);

    for (const CubeTile* tile : tiles)
    {
        const auto& bounds = tile->GetBounds();
        auto cubeTop = GetConvexPoints(bounds.GetTop());

        for (auto& p : playerBottom)
        {
            if (polygonsIntersect({p}, cubeTop))
            {
                result.push_back(tile);
                break;
            }
        }
    }
    return result;
}

std::vector<sf::Vector2f> Collision::PlayerBottomPoints(const sf::RectangleShape& player)
{
    sf::Vector2f size = player.getSize();
    sf::Transform t = player.getTransform();
    
    std::vector<sf::Vector2f> points;
    points.push_back(t.transformPoint(sf::Vector2f(0.f, size.y)));
    points.push_back(t.transformPoint(sf::Vector2f(size.x, size.y)));
    return points;
}

std::vector<sf::Vector2f> Collision::PlayerTopPoints(const sf::RectangleShape& player)
{
    sf::Vector2f size = player.getSize();
    sf::Transform t = player.getTransform();
    
    std::vector<sf::Vector2f> points;
    points.push_back(t.transformPoint(sf::Vector2f(0.f, 0.f)));
    points.push_back(t.transformPoint(sf::Vector2f(size.x, size.y)));
    return points;
}

std::vector<sf::Vector2f> Collision::GetConvexPoints(const sf::ConvexShape& shape)
{
    std::vector<sf::Vector2f> pts;
    for (size_t i = 0; i < shape.getPointCount(); i++)
    {
        pts.push_back(shape.getTransform().transformPoint(shape.getPoint(i)));
    }
    return pts;
}

//-----Collision-----

bool Collision::PlayerVsCubeTileSAT(const sf::RectangleShape& playerRect, const std::vector<CubeTile*>& tiles)
{
    auto playerBottom = PlayerBottomPoints(playerRect);
    auto playerTop = PlayerTopPoints(playerRect);

    for (auto* tile : tiles)
    {
        const auto& bounds = tile->GetBounds();

        auto cubeTop = GetConvexPoints(bounds.GetTop());
        for (auto& p : playerTop)
        {
            if (polygonsIntersect({p}, cubeTop))
            {
                std::cout << "player hit top of tile at " << tile->m_gridCoords.x << "," << tile->m_gridCoords.y << std::endl;
            }
        }

        auto cubeLeft = GetConvexPoints(bounds.GetWallLeft());
        auto cubeRight = GetConvexPoints(bounds.GetWallRight());
        auto cubeBackL = GetConvexPoints(bounds.GetWallBackL());
        auto cubeBackR = GetConvexPoints(bounds.GetWallBackR());

        float cubeTopY = cubeTop[0].y;
        float playerY = playerBottom[0].y;

        if (playerY <= cubeTopY)
        {
            if (polygonsIntersect(playerBottom, cubeLeft))
                std::cout << "hit left wall" << std::endl;
            if (polygonsIntersect(playerBottom, cubeRight))
                std::cout << "hit right wall" << std::endl;
            if (polygonsIntersect(playerBottom, cubeBackL))
                std::cout << "hit back left wall" << std::endl;
            if (polygonsIntersect(playerBottom, cubeBackR))
                std::cout << "hit back right wall" << std::endl;
        }
    }


    return false;
}
