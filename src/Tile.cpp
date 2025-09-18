#include "Tile.h"
#include "Math.h"
#include <iostream>

Tile::Tile(const sf::Vector2f& tileSize, const sf::Vector3f& tilePos) :
    m_tileSize(tileSize), 
    m_scale(1.f), 
    m_tilePos(tilePos),
    sheetIdx(0)
{
    Initialize();
}

Tile::~Tile()
{
}

void Tile::Initialize()
{
    m_scale = Math::CalcScale(m_tileSize);
    m_tileSize *= m_scale;
}

void Tile::Load()
{
    SheetManager::Load();
    SetActiveSheet(SheetID::Floor);

    SheetLoader& sheet = SheetManager::Get(activeSheedID);
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
    m_texture = sheet.m_texture;
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sheet.frames[0].rect);
    m_sprite.setScale(m_scale, m_scale);
}
