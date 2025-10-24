#pragma once
#include <SFML/Graphics.hpp>

#include "MapLoader.h"
#include "CubeTile.h"


class TileMap
{
    public:
        std::vector<std::vector<std::vector<CubeTile>>> m_tiles;
        sf::Vector2f m_tileSize;

        int m_width;
        int m_height;
        int m_layers;

        sf::Vector2f m_mapOffset;

        MapLoader mapLoader;
        MapData md;

    public:
        TileMap(const std::string& mapFile, sf::Vector2f tileSize, sf::Vector2f mapOffset);
        ~TileMap();
        
        void Initialize();
        void Load(const std::string& mapFile);
        void Draw(sf::RenderWindow& window);

        std::vector<CubeTile*> GetAllTiles();
        void Reset();
};
