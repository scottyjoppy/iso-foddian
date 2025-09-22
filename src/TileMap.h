#pragma once
#include "CubeTile.h"

#include <SFML/Graphics.hpp>

class TileMap
{
    public:
        std::vector<std::vector<std::vector<CubeTile>>> m_cubeTiles;
        sf::Vector2f m_tileSize;

        float m_scale;

        int m_width;
        int m_height;
        int m_layers;

    public:
        TileMap(int width, int height, int layers, sf::Vector2f tileSize, sf::Vector2f mapOffset);
        ~TileMap();
        
        void Initialize();
        void Draw(sf::RenderWindow& window);
};
