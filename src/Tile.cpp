#include "Tile.h"
#include <iostream>

Tile::Tile(const sf::Vector2f& tileSize, const sf::Vector2i& gridIndex, const sf::Vector2f& pos, float depth, float scale)
    : m_size(tileSize), m_gridIndex(gridIndex), m_pos(pos), m_depth(depth), m_sides(3), m_scale(scale)
{
    Initialize();
    IsoTransform();
}

Tile::~Tile()
{
}

void Tile::Initialize()
{
    float halfW = m_size.x / 2.f * m_scale;
    float halfH = m_size.y / 2.f * m_scale;
    float dScaled = m_depth * m_scale;

    m_faces.resize(m_sides);
    for (auto& f : m_faces) f.setPointCount(4);

    // --- Right face ---
    m_faces[0].setPoint(0, {halfW, 0.f});
    m_faces[0].setPoint(1, {0.f, halfH});
    m_faces[0].setPoint(2, {0.f, halfH - dScaled});
    m_faces[0].setPoint(3, {halfW, -dScaled});

    // --- Left face ---
    m_faces[1].setPoint(0, {-halfW, 0.f});
    m_faces[1].setPoint(1, {0.f, halfH});
    m_faces[1].setPoint(2, {0.f, halfH - dScaled});
    m_faces[1].setPoint(3, {-halfW, -dScaled});

    // --- Top face ---
    m_faces[2].setPoint(0, {0.f, -halfH});
    m_faces[2].setPoint(1, {halfW, 0.f});
    m_faces[2].setPoint(2, {0.f, halfH});
    m_faces[2].setPoint(3, {-halfW, 0.f});

    size_t i = 0;
    for (auto& f : m_faces)
    {
        f.setFillColor(sf::Color(50 * i, 50 * i, 50 * i));
        f.setOutlineColor(sf::Color::Black);
        f.setOutlineThickness(1.f);
        f.setOrigin(0.f, 0.f);
        i++;
    }
}
void Tile::IsoTransform()
{
    float isoX = (m_gridIndex.x - m_gridIndex.y) * (m_size.x / 2.f) * m_scale + m_pos.x;
    float isoY = (m_gridIndex.x + m_gridIndex.y) * (m_size.y / 2.f) * m_scale + m_pos.y;

    for (int i = 0; i < m_sides - 1; i++) m_faces[i].setPosition(isoX, isoY);

    m_faces[2].setPosition(isoX, isoY - m_depth * m_scale);
}

void Tile::Draw(sf::RenderWindow& window)
{
    if (m_depth > 0)
        for (auto& f : m_faces) window.draw(f);
    else
        window.draw(m_faces[2]);
}
