#include "TileMap.h"
#include <iostream>
#include "Math.h"

TileMap::TileMap(const std::string& mapFile, sf::Vector2f tileSize, sf::Vector2f mapOffset) :
    m_tileSize(tileSize), m_mapOffset(mapOffset)
{
    Load(mapFile);
}

TileMap::~TileMap()
{
}

void TileMap::Initialize()
{
}

void TileMap::Load(const std::string& mapFile)
{
    if (!mapLoader.Load(mapFile, md))
    {
        std::cerr << "Failed to load map: " << mapFile << std::endl;
        return;
    }

    m_width = md.mapW;
    m_height = md.mapH;
    m_layers = 2;

    m_tiles.resize(m_layers);
    for (int y = 0; y < m_layers; y++)
    {
        m_tiles[y].resize(m_height);
        for (int z = 0; z < m_height; z++)
        {
            for (int x = 0; x < m_width; x++)
            {
                int index = (y * m_height + z) * m_width + x;
                int tileId = md.tileIds[index];
                m_tiles[y][z].emplace_back
                    (
                     m_tileSize,
                     sf::Vector3i(x, y, z),
                     tileId,
                     m_mapOffset,
                     1
                    );
            }
        }
    }
}


void TileMap::Draw(sf::RenderWindow& window)
{
    for (auto& layer : m_tiles)
    {
        for (auto& row : layer)
        {
            for (auto& tile : row)
            {
                tile.Draw(window);
            }
        }
    }
}

std::vector<CubeTile*> TileMap::GetAllTiles()
{
    std::vector<CubeTile*> allTiles;
    for (auto& layer : m_tiles)
    {
        for (auto& row : layer)
        {
            for (auto& tile : row)
            {
                allTiles.push_back(&tile);
            }
        }
    }
    return allTiles;
}
