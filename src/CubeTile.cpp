#include "CubeTile.h"
#include "SheetManager.h"

#include "Math.h"
#include <iostream>

CubeTile::CubeTile(const sf::Vector2f& tileSize, sf::Vector3i gridCoords, int tileId, const sf::Vector2f& mapOffset, int logicalHeight) :
    m_tileSize(tileSize), m_gridCoords(gridCoords), m_mapOffset(mapOffset), m_scale(1.f), m_cubeHeight(0), m_logicalHeight(logicalHeight), m_tileId(tileId), debugging(false)
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
    sf::Vector2f pos = Math::IsoTransform(sf::Vector3f(m_gridCoords), m_tileSize * m_scale);

    m_mapPos = pos + m_mapOffset;
    m_sprite.setPosition(m_mapPos);
    m_sprite.setScale(m_scale * 2.f, m_scale * 2.f);

    m_cubeHeight = m_tileSize.y * m_scale;
 }

void CubeTile::Update(float deltaTime)
{
    if (m_tileId && debugging)
    {
        m_bounds.SetOrigin({m_tileSize.x * m_scale / 2, 0});
        if (m_cubeHeight > 0.f)
        {
            m_bounds.BuildTop(m_mapPos, m_tileSize * m_scale, m_cubeHeight);
            m_bounds.BuildWallLeft(m_mapPos, m_tileSize * m_scale, m_cubeHeight);
            m_bounds.BuildWallRight(m_mapPos, m_tileSize * m_scale, m_cubeHeight);
            m_bounds.BuildWallBackL(m_mapPos, m_tileSize * m_scale, m_cubeHeight);
            m_bounds.BuildWallBackR(m_mapPos, m_tileSize * m_scale, m_cubeHeight);
        }
        m_bounds.BuildBottom(m_mapPos, m_tileSize * m_scale);
    }

    if (m_tileId)
    {
        SetTile(m_tileId);
    }
}

void CubeTile::Draw(sf::RenderWindow& window)
{
    if (m_tileId)
        window.draw(m_sprite);

    if (debugging)
    {
        window.draw(m_bounds.GetTop());
        window.draw(m_bounds.GetBottom());
        window.draw(m_bounds.GetWallLeft());
        window.draw(m_bounds.GetWallRight());
        window.draw(m_bounds.GetWallBackL());
        window.draw(m_bounds.GetWallBackR());
    }
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
