#include "Tile.h"
#include "Math.h"
#include <iostream>

Tile::Tile(const sf::Vector2f& tileSize, sf::Vector3i gridCoords) :
    m_tileSize(tileSize), 
    m_scale(1.f), 
    m_gridCoords(gridCoords),
    sheetIdx(0)
{
    Initialize();
    Load();
}

Tile::~Tile()
{
}

void Tile::Initialize()
{
}

void Tile::Load()
{
    SetActiveSheet(SheetID::Floor);

    SheetLoader& sheet = SheetManager::Get(activeSheetID);
}

void Tile::Draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void Tile::SetActiveSheet(SheetID id)
{
    activeSheetID = id;
    sheetIdx = 0;

    auto& sheet = SheetManager::Get(id);
    m_texture = &sheet.m_texture;
    m_sprite.setTexture(*m_texture);
    m_sprite.setTextureRect(sheet.frames[0].rect);
    m_sprite.setScale(sheet.m_scale, sheet.m_scale);
}
