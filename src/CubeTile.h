#pragma once
#include <SFML/Graphics.hpp>

#include "Tile.h"

class CubeTile
{
    public:
        Tile m_top;
        Tile m_left;
        Tile m_right;

    public:
        CubeTile(const sf::Vector2f& tileSize, sf::Vector3i gridCoords, const sf::Vector2f& mapOffset);
        ~CubeTile();

        void Initialize();
        void Draw(sf::RenderWindow& window);
};
