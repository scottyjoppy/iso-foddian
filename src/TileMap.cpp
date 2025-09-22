#include "TileMap.h"
#include <iostream>
#include "Math.h"

TileMap::TileMap(int width, int height, int layers, sf::Vector2f tileSize, sf::Vector2f mapOffset) :
    m_width(width), m_height(height), m_layers(layers), m_tileSize(tileSize)
{
    Initialize();
    m_cubeTiles.resize(layers);
    for (int z = 0; z < layers; z++)
    {
        m_cubeTiles[z].resize(height);
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                m_cubeTiles[z][y].emplace_back(tileSize, sf::Vector3i(x, y, z), mapOffset);
            }
        }
    }
}

TileMap::~TileMap()
{
}

void TileMap::Initialize()
{
    std::cout << "Initializing TileMap" << std::endl;
    m_scale = Math::CalcScale(m_tileSize);
}

void TileMap::Draw(sf::RenderWindow& window)
{
    for (auto& layer : m_cubeTiles)
    {
        for (auto& row : layer)
        {
            for (auto& cube : row)
            {
                cube.Draw(window);
            }
        }
    }
}
