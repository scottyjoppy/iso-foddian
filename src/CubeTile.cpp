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

    sf::Vector2f mapPos = pos + m_mapOffset;
    m_sprite.setPosition(mapPos);
    m_sprite.setScale(m_scale * 2.f, m_scale * 2.f);

    float cubeHeight = m_tileSize.y * m_scale;

    mapPos += sf::Vector2f(m_tileSize.x * m_scale / 2, 0);

    if (cubeHeight > 0.f)
    {
        m_bounds.BuildTop(mapPos, m_tileSize * m_scale, cubeHeight);
        m_bounds.BuildWallLeft(mapPos, m_tileSize * m_scale, cubeHeight);
        m_bounds.BuildWallRight(mapPos, m_tileSize * m_scale, cubeHeight);
        m_bounds.BuildWallBackL(mapPos, m_tileSize * m_scale, cubeHeight);
        m_bounds.BuildWallBackR(mapPos, m_tileSize * m_scale, cubeHeight);
    }
    m_bounds.BuildBottom(mapPos, m_tileSize * m_scale);
}

void CubeTile::Draw(sf::RenderWindow& window)
{
    //window.draw(m_sprite);

    window.draw(m_bounds.GetTop());
    window.draw(m_bounds.GetBottom());
    window.draw(m_bounds.GetWallLeft());
    window.draw(m_bounds.GetWallRight());
    window.draw(m_bounds.GetWallBackL());
    window.draw(m_bounds.GetWallBackR());
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
