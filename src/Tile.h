#pragma once

#include <SFML/Graphics.hpp>

class Tile
{
    public:
        std::vector <sf::Sprite> m_sprites;

        sf::Vector2f m_pos;
        sf::Vector2f m_color;
        sf::Vector2i m_tileSize;
        sf::Vector2i m_gridIndex;
        sf::Vector2f m_scale;

        int m_sides;
        float m_depth;

        sf::Texture* m_texture;

    public:
        Tile(const sf::Vector2i& tileSize, const sf::Vector2i& gridIndex, const sf::Vector2f& pos, float depth, sf::Texture* tex);
        ~Tile();

        void Initialize();
        void SetGridPos(sf::Vector2f pos);
        void Draw(sf::RenderWindow& window);
        void IsoTransform();
};
