#include "CubeTile.h"
#include "SheetManager.h"

#include "Math.h"
#include <iostream>

CubeTile::CubeTile(const sf::Vector2f& tileSize, sf::Vector3i gridCoords, int tileId, const sf::Vector2f& mapOffset) :
    m_tileSize(tileSize), m_gridCoords(gridCoords), m_mapOffset(mapOffset), m_scale(1.f)
{
    SetTile(tileId);
    Initialize();
}

CubeTile::~CubeTile()
{
}

void CubeTile::Initialize()
{
    m_scale = Math::CalcScale(m_tileSize);
    sf::Vector2f pos = Math::IsoTransform(m_gridCoords.x, m_gridCoords.y, m_gridCoords.z, m_tileSize * m_scale);
    m_sprite.setPosition(pos + m_mapOffset);
    m_sprite.setScale(m_scale * 2.f, m_scale * 2.f);

    m_bounds.setPointCount(4);
    m_bounds.setPoint(0, {0.f, 0.f});
    m_bounds.setPoint(1, {m_tileSize.x * m_scale, 0.f});
    m_bounds.setPoint(2, {m_tileSize.x * m_scale, m_tileSize.y * m_scale});
    m_bounds.setPoint(3, {0.f, m_tileSize.y * m_scale});
    m_bounds.setPosition(pos + m_mapOffset);
}

void CubeTile::Draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void CubeTile::SetTile(int tileId)
{
    auto& sheet = SheetManager::Get(SheetID::TileSheet);
    m_sprite.setTexture(sheet.m_texture);

    if (tileId < sheet.frames.size())
        m_sprite.setTextureRect(sheet.frames[tileId].rect);
    else
        std::cerr << "Warning: invalid tileId " << tileId << std::endl;
    m_sprite.setOrigin(sheet.m_origin);

}
