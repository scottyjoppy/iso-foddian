#pragma once
#include <SFML/Graphics.hpp>

#include "Tile.h"

class CubeTile
{
    public:
        sf::Sprite m_sprite;
        sf::Vector3i m_gridCoords;
        sf::Vector2f m_tileSize;
        sf::Vector2f m_mapOffset;
        float m_scale;

        sf::ConvexShape m_bounds;

    public:
        CubeTile(const sf::Vector2f& tileSize, sf::Vector3i gridCoords, int tileId, const sf::Vector2f& mapOffset);
        ~CubeTile();

        void Initialize();
        void Draw(sf::RenderWindow& window);
        void SetTile(int tileId);
};
