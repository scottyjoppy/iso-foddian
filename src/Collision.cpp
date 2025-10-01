#include <iostream>

#include "Math.h"
#include "Collision.h"


bool Collision::NearTiles(const sf::Vector3f& obj1, const sf::Vector3f& obj2)
{
   float dist = Math::GetDist(obj1, obj2);
   return dist <= 3;
}

bool Collision::AABB(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
{
	if (
			rect1.left + rect1.width > rect2.left &&
			rect2.left + rect2.width > rect1.left &&
			rect2.top + rect2.height > rect1.top &&
			rect1.top + rect1.height > rect2.top
	   )
		return true;
	return false;
}

bool Collision::LineLine(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, const sf::Vector2f& p4)
{
    float denom = ( (p4.y - p3.y) * (p2.x - p1.x) ) - ( (p4.x - p3.x) * (p2.y - p1.y) );
    if (denom == 0.0f) return false;

    float uA = ( (p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x) ) / denom;
    float uB = ( (p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x) ) / denom;

    return (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1);
}

bool Collision::PolyLine(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& l1, const sf::Vector2f& l2)
{
    for (size_t i = 0; i < vertices.size(); i++)
    {
        size_t next = (i + 1) % vertices.size();
        if (LineLine(l1, l2, vertices[i], vertices[next]))
        {
            std::cout << "something" << std::endl;
            return true;
        }
    }
    return false;
}

std::vector<CubeTile*> Collision::BroadPhase(std::vector<CubeTile*>& allTiles, Player& p)
{
    std::vector<CubeTile*> collidingTiles;

    sf::FloatRect playerBox = p.m_bounds.getGlobalBounds();

    sf::Vector2f feet(p.m_mapPos.x, p.m_mapPos.y + playerBox.height);
    sf::Vector2f down(feet.x, feet.y + 3.f);
    for (auto& t : allTiles)
    {
        // Check nearby tiles
        if (NearTiles(p.m_gridPos, sf::Vector3f
                    (
                     static_cast<float>(t->m_gridCoords.x),
                     static_cast<float>(t->m_gridCoords.y),
                     static_cast<float>(t->m_gridCoords.z)
                    )))
        {
            // AABB check
            sf::FloatRect tileBox = t->m_boundBox;

            if (AABB(playerBox, tileBox))
            {
                std::vector<sf::Vector2f> poly = t->m_bounds.GetVertices();
                if (PolyLine(poly, feet, down))
                {
                    std::cout << "test" << std::endl;
                    collidingTiles.push_back(t);
                }
            }
        }
    }
    return collidingTiles;
}
