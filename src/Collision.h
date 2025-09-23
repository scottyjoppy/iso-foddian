#pragma once
#include <SFML/Graphics.hpp>

#include "CubeTile.h"

class Collision
{
    public:
        inline static float m_g = 0.f;
        inline static float m_b = 0.f;
        inline static float m_f = 0.f;

    public:
        static std::vector<const CubeTile*> TilesUnderPlayer(const sf::RectangleShape& playerRect, const std::vector<CubeTile*>& tiles);
        static std::vector<sf::Vector2f> PlayerBottomPoints(const sf::RectangleShape& player);
        static std::vector<sf::Vector2f> PlayerTopPoints(const sf::RectangleShape& player);
        static std::vector<sf::Vector2f> GetConvexPoints(const sf::ConvexShape& shape);
        static bool PlayerVsCubeTileSAT(const sf::RectangleShape& playerRect, const std::vector<CubeTile*>& tiles);

};
