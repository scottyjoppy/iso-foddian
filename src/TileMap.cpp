#include "TileMap.h"
#include "Math.h"

TileMap::TileMap(int width, int height, int layers, sf::Vector2f tileSize) :
    m_width(width), m_height(height), m_layers(layers), m_tileSize(tileSize)
{
    m_tiles.resize(layers);
    for (int z = 0; z < layers; z++)
    {
        m_tiles[z].resize(height);
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                m_tiles[z][y].emplace_back(tileSize, sf::Vector3i(x, y, z));
            }
        }
    }
    Initialize();
}

TileMap::~TileMap()
{
}

void TileMap::Initialize()
{
    m_scale = Math::CalcScale(m_tileSize);
}

void TileMap::Draw(sf::RenderWindow& window, sf::Vector2f mapOffset)
{
    for (auto& layer : m_tiles)
    {
        for (auto& row : layer)
        {
            for (auto& tile : row)
            {
                sf::Vector2f pos = Math::IsoTransform(tile.m_gridCoords.x, tile.m_gridCoords.y, tile.m_gridCoords.z, tile.m_tileSize) * m_scale;
                tile.m_sprite.setPosition(pos + mapOffset);
                tile.Draw(window);
            }
        }
    }
}
