#include <iostream>
#include "Math.h"
#include "SheetLoader.h"

SheetLoader::SheetLoader(std::string fileDir, sf::Vector2i tileSize, sf::Vector2i spriteSize, sf::Vector2f origin) :
    m_fileDir(fileDir), m_tileSize(tileSize), m_spriteSize(spriteSize), m_origin(origin)
{
    Initialize();
}

SheetLoader::~SheetLoader()
{
}

void SheetLoader::Initialize()
{
    m_scale = Math::CalcScale(m_spriteSize);
}

void SheetLoader::Load()
{
    if (!m_texture.loadFromFile(m_fileDir))
        std::cout << "Failed to load " << m_fileDir << std::endl;
    else
        std::cout << "Successfully loaded " << m_fileDir << std::endl;

    m_sheetSize = {m_texture.getSize().x, m_texture.getSize().y};

    int m_totalTilesX = m_sheetSize.x / m_tileSize.x;
    int m_totalTilesY = m_sheetSize.y / m_tileSize.y;

    int m_totalTiles = m_totalTilesX * m_totalTilesY;

    frames.resize(m_totalTiles);

    for (size_t y = 0; y < m_totalTilesY; y++)
    {
        for (size_t x = 0; x < m_totalTilesX; x++)
        {
            int i = x + y * m_totalTilesX;

            int offsetX = (m_tileSize.x - m_spriteSize.x) / 2;
            int offsetY = (m_tileSize.y - m_spriteSize.y) / 2;

            frames[i].id = i;
            frames[i].rect = sf::IntRect
                (
                 x * m_tileSize.x + offsetX,
                 y * m_tileSize.y + offsetY,
                 m_spriteSize.x,
                 m_spriteSize.y
                );
        }
    }
}
