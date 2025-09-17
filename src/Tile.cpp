#include "Tile.h"
#include "Math.h"
#include <iostream>

Tile::Tile(const sf::Vector2i& tileSize, const sf::Vector2i& gridIndex, const sf::Vector2f& pos, float depth)
    : m_size(tileSize), m_gridIndex(gridIndex), m_pos(pos), m_depth(depth), m_sides(3), m_scale(1.f, 1.f)
{
    Initialize();
    IsoTransform();
}

Tile::~Tile()
{
}

void Tile::Initialize()
{
    m_scale = Math::CalcScale(m_size);
    m_sprites.resize(m_sides);

    if (!m_texture.loadFromFile("assets/textures/tiles/tiletop.png"))
        std::cerr << "Failed to load texture\n";
    //m_texture.setSmooth(false);

    for (auto& sprite : m_sprites)
    {
        sprite.setTexture(m_texture);
        sprite.setScale(6.f, 6.f);
        sprite.setPosition(800, 200);
    }
}
void Tile::IsoTransform()
{
    float isoX = (m_gridIndex.x - m_gridIndex.y) * (m_size.x / 2.f) * m_scale.x + m_pos.x;
    float isoY = (m_gridIndex.x + m_gridIndex.y) * (m_size.y / 2.f) * m_scale.y + m_pos.y;

    for (int i = 0; i < m_sides - 1; i++) m_sprites[i].setPosition(isoX, isoY);

    m_sprites[2].setPosition(isoX, isoY);
}

void Tile::Draw(sf::RenderWindow& window)
{
    for (auto& s : m_sprites) window.draw(s);
}
