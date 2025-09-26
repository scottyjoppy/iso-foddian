#include "Tile.h"
#include "Math.h"
#include <iostream>

Tile::Tile(const sf::Vector2f& tileSize, sf::Vector3i gridCoords, SheetID sheetID, const sf::Vector2f& mapOffset) :
    m_tileSize(tileSize), 
    m_scale(1.f),
    m_gridCoords(gridCoords),
    activeSheetID(sheetID),
    m_mapOffset(mapOffset)
{
    SetActiveSheet(activeSheetID);
    Initialize();
    Load();
}

Tile::~Tile()
{
}

void Tile::Initialize()
{
    m_scale = Math::CalcScale(m_tileSize);
    sf::Vector2f pos = Math::IsoTransform(sf::Vector3f(m_gridCoords), m_tileSize * m_scale);
    
    m_sprite.setPosition(pos + m_mapOffset);
    m_sprite.setScale(m_scale * 2.f, m_scale * 2.f);
}

void Tile::Load()
{
}

void Tile::Draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void Tile::SetActiveSheet(SheetID id)
{
    activeSheetID = id;

    auto& sheet = SheetManager::Get(id);
    m_texture = &sheet.m_texture;
    m_sprite.setTexture(*m_texture);

    if (!sheet.frames.empty())
        m_sprite.setTextureRect(sheet.frames[0].rect);
    else
        std::cerr << "Warning: Sheet " << static_cast<int>(id) << " has no frames!" << std::endl;
    m_sprite.setOrigin(sheet.m_origin);
}
