#include "CubeTile.h"
#include <iostream>
#include "Math.h"
#include "SheetManager.h"

CubeTile::CubeTile(const sf::Vector2f& tileSize, sf::Vector3i gridCoords, const sf::Vector2f& mapOffset) :
    m_top(tileSize, gridCoords, SheetID::Top, mapOffset), 
    m_left(tileSize, gridCoords, SheetID::Left, mapOffset), 
    m_right(tileSize,gridCoords, SheetID::Right, mapOffset)
{
    Initialize();
}

CubeTile::~CubeTile()
{
}

void CubeTile::Initialize()
{
}

void CubeTile::Draw(sf::RenderWindow& window)
{
    m_left.Draw(window);
    m_right.Draw(window);
    m_top.Draw(window);
}
