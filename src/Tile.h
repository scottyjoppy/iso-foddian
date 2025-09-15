#pragma once

#include <SFML/Graphics.hpp>

class Tile
{
    public:
        sf::ConvexShape m_top;
        sf::ConvexShape m_left;
        sf::ConvexShape m_right;

        sf::Vector2f m_pos;
        sf::Vector2f m_color;
        sf::Vector2f m_size;
        sf::Vector2i m_gridIndex;
        float m_depth;

    public:
        Tile(const sf::Vector2f& tileSize, const sf::Vector2i& gridIndex, const sf::Vector2f& pos, float depth);
        ~Tile();

        void Initialize();
        void SetGridPos(sf::Vector2f pos);
        void Draw(sf::RenderWindow& window);
        void IsoTransform();
};
