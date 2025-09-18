#include "Tile.h"
#include "Math.h"
#include <iostream>

Tile::Tile(const sf::Vector2i& tileSize, const sf::Vector2i& gridIndex, const sf::Vector2f& pos, float depth, sf::Texture* tex)
    : m_tileSize(tileSize), m_gridIndex(gridIndex), m_pos(pos), m_depth(depth), m_sides(3), m_scale(1.f, 1.f), m_texture(tex)
{
    Initialize();
    IsoTransform();
}

Tile::~Tile()
{
}

void Tile::Initialize()
{

    float tempScale = Math::CalcScale(sf::Vector2f(m_tileSize.y, m_tileSize.y));
    m_scale = {tempScale, tempScale};
    m_sprites.resize(m_sides);

    for (auto& sprite : m_sprites)
    {
        sprite.setTexture(*m_texture);
        sprite.setScale(m_scale);
    }
}
void Tile::IsoTransform()
{
    float isoX = (m_gridIndex.x - m_gridIndex.y) * (m_tileSize.x / 2.f * m_scale.x - m_tileSize.x * 1.5f) + m_pos.x - (m_tileSize.x * m_scale.x / 4.f);
    float isoY = (m_gridIndex.x + m_gridIndex.y) * (m_tileSize.y / 2.f * m_scale.y - m_tileSize.y * 1.5f) + m_pos.y;

    for (auto& s : m_sprites) s.setPosition(isoX, isoY);
}

void Tile::Draw(sf::RenderWindow& window)
{
    for (auto& s : m_sprites) window.draw(s);
}
