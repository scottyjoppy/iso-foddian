#pragma once

#include <SFML/Graphics.hpp>

class Tile
{
    public:
        std::vector <sf::ConvexShape> m_faces;

        sf::Vector2f m_pos;
        sf::Vector2f m_color;
        sf::Vector2f m_size;
        sf::Vector2i m_gridIndex;
        float m_scale;

        int m_sides;
        float m_depth;

    public:
        Tile(const sf::Vector2f& tileSize, const sf::Vector2i& gridIndex, const sf::Vector2f& pos, float depth, float scale);
        ~Tile();

        void Initialize();
        void SetGridPos(sf::Vector2f pos);
        void Draw(sf::RenderWindow& window);
        void IsoTransform();
};
