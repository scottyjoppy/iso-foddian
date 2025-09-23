#include "TileBounds.h"


TileBounds::TileBounds()
{
}

TileBounds::~TileBounds()
{
}

void TileBounds::BuildTop(const sf::Vector2f& pos, const sf::Vector2f& size, float height)
{
    // Diamond shape (top face of iso tile)
    m_top.setPointCount(4);
    m_top.setPoint(0, {pos.x, pos.y - height});                             // top
    m_top.setPoint(1, {pos.x + size.x / 2, pos.y + size.y / 2 - height});   // right
    m_top.setPoint(2, {pos.x, pos.y + size.y - height});                    // bottom
    m_top.setPoint(3, {pos.x - size.x / 2, pos.y + size.y / 2 - height});   // left
    m_top.setFillColor(sf::Color(0, 255, 0, 80)); // debug translucent
}

void TileBounds::BuildBottom(const sf::Vector2f& pos, const sf::Vector2f& size)
{
    // Same diamond but shifted down by height
    m_bottom.setPointCount(4);
    m_bottom.setPoint(0, {pos.x, pos.y});
    m_bottom.setPoint(1, {pos.x + size.x / 2, pos.y + size.y / 2});
    m_bottom.setPoint(2, {pos.x, pos.y + size.y});
    m_bottom.setPoint(3, {pos.x - size.x / 2, pos.y + size.y / 2});
    m_bottom.setFillColor(sf::Color(255, 0, 0, 80)); // debug translucent
}

void TileBounds::BuildWallLeft(const sf::Vector2f& pos, const sf::Vector2f& size, float height)
{
    // Left edge connects top-left and bottom-left
    m_left.setPointCount(4);
    m_left.setPoint(0, {pos.x - size.x / 2, pos.y + size.y / 2});
    m_left.setPoint(1, {pos.x, pos.y + size.y});
    m_left.setPoint(2, {pos.x, pos.y + size.y  - height});
    m_left.setPoint(3, {pos.x - size.x / 2, pos.y + size.y / 2  - height});
    m_left.setFillColor(sf::Color(0, 0, 255, 80));
}

void TileBounds::BuildWallRight(const sf::Vector2f& pos, const sf::Vector2f& size, float height)
{
    // Right edge connects top-right and bottom-right
    m_right.setPointCount(4);
    m_right.setPoint(0, {pos.x, pos.y + size.y});
    m_right.setPoint(1, {pos.x + size.x / 2, pos.y + size.y / 2});
    m_right.setPoint(2, {pos.x + size.x / 2, pos.y + size.y / 2  - height});
    m_right.setPoint(3, {pos.x, pos.y + size.y  - height});
    m_right.setFillColor(sf::Color(255, 255, 0, 80));
}

void TileBounds::BuildWallBackL(const sf::Vector2f& pos, const sf::Vector2f& size, float height)
{
    // Back left edge connects top-top and left
    m_backL.setPointCount(4);
    m_backL.setPoint(0, {pos.x, pos.y});
    m_backL.setPoint(1, {pos.x - size.x / 2, pos.y + size.y / 2});
    m_backL.setPoint(2, {pos.x - size.x / 2, pos.y + size.y / 2  - height});
    m_backL.setPoint(3, {pos.x, pos.y  - height});
    m_backL.setFillColor(sf::Color(0, 255, 255, 80));
}

void TileBounds::BuildWallBackR(const sf::Vector2f& pos, const sf::Vector2f& size, float height)
{
    // Back right edge connects top-top and right
    m_backR.setPointCount(4);
    m_backR.setPoint(0, {pos.x, pos.y});
    m_backR.setPoint(1, {pos.x + size.x / 2, pos.y + size.y / 2});
    m_backR.setPoint(2, {pos.x + size.x / 2, pos.y + size.y / 2  - height});
    m_backR.setPoint(3, {pos.x, pos.y  - height});
    m_backR.setFillColor(sf::Color(255, 0, 255, 80));
}
