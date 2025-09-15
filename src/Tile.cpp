#include "Tile.h"

Tile::Tile(const sf::Vector2f& tileSize, const sf::Vector2i& gridIndex, const sf::Vector2f& pos, float depth)
    : m_size(tileSize), m_gridIndex(gridIndex), m_pos(pos), m_depth(depth)
{
    Initialize();
    IsoTransform();
}

Tile::~Tile()
{
}

void Tile::Initialize()
{
    float halfW = m_size.x / 2.f;
    float halfH = m_size.y / 2.f;
    float depth = m_depth; // depth in pixels 

    // --- Top face ---
    m_top.setPointCount(4);
    m_top.setPoint(0, {0.f, -halfH});
    m_top.setPoint(1, {halfW, 0.f});
    m_top.setPoint(2, {0.f, halfH});
    m_top.setPoint(3, {-halfW, 0.f});
    m_top.setFillColor(sf::Color::Red);
    m_top.setOutlineColor(sf::Color::Black);
    m_top.setOutlineThickness(1.f);
    m_top.setOrigin(0.f, 0.f); // origin at center

    // --- Left face ---
    m_left.setPointCount(4);
    m_left.setPoint(0, {-halfW, 0.f});
    m_left.setPoint(1, {0.f, halfH});
    m_left.setPoint(2, {0.f, halfH + depth});
    m_left.setPoint(3, {-halfW, depth});
    m_left.setFillColor(sf::Color(200, 200, 200));
    m_left.setOutlineColor(sf::Color::Black);
    m_left.setOutlineThickness(1.f);
    m_left.setOrigin(0.f, 0.f);

    // --- Right face ---
    m_right.setPointCount(4);
    m_right.setPoint(0, {halfW, 0.f});
    m_right.setPoint(1, {0.f, halfH});
    m_right.setPoint(2, {0.f, halfH + depth});
    m_right.setPoint(3, {halfW, depth});
    m_right.setFillColor(sf::Color(150, 150, 150));
    m_right.setOutlineColor(sf::Color::Black);
    m_right.setOutlineThickness(1.f);
    m_right.setOrigin(0.f, 0.f);
}
void Tile::IsoTransform()
{
    float isoX = (m_gridIndex.x - m_gridIndex.y) * (m_size.x / 2.f) + m_pos.x;
    float isoY = (m_gridIndex.x + m_gridIndex.y) * (m_size.y / 2.f) + m_pos.y;

    m_top.setPosition(isoX, isoY);
    m_left.setPosition(isoX, isoY);
    m_right.setPosition(isoX, isoY);
}

void Tile::Draw(sf::RenderWindow& window)
{
    window.draw(m_left);
    window.draw(m_right);
    window.draw(m_top);
}
