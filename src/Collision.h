#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

#include "Player.h"
#include "CubeTile.h"

struct Line
{
    sf::Vector2f p1;
    sf::Vector2f p2;
};

using Polygon = std::vector<sf::Vector2f>;

class Collision
{
    public:
        inline static float m_g = 0.f;
        inline static float m_b = 0.f;
        inline static float m_f = 0.f;

    public:
        static bool NearTiles(const sf::Vector3f& obj1, const sf::Vector3f& obj2);
        static bool AABB(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
        static std::vector<CubeTile*> BroadPhase(std::vector<CubeTile*>& allTiles, Player& p);
        static bool LinePolygon(const Line& line, const Polygon& poly);
};
