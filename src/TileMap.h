#pragma once
#include "Tile.h"

#include <SFML/Graphics.hpp>

class TileMap
{
    public:
        std::vector<std::vector<std::vector<Tile>>> m_tiles;
        sf::Vector2f m_tileSize;

        float m_scale;

        int m_width;
        int m_height;
        int m_layers;

    public:
        TileMap(int width, int height, int layers, sf::Vector2f tileSize);
        ~TileMap();
        
        void Initialize();
        void Draw(sf::RenderWindow& window, sf::Vector2f offset);
};
