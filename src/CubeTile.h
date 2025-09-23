#pragma once
#include <SFML/Graphics.hpp>

#include "TileBounds.h"

class CubeTile
{
    public:
        sf::Sprite m_sprite;
        sf::Vector3i m_gridCoords;
        sf::Vector2f m_tileSize;
        sf::Vector2f m_mapOffset;
        float m_scale;

        TileBounds m_bounds;

    public:
        CubeTile(const sf::Vector2f& tileSize, sf::Vector3i gridCoords, int tileId, const sf::Vector2f& mapOffset);
        ~CubeTile();

        void Initialize();
        void Draw(sf::RenderWindow& window);
        void SetTile(int tileId);

        const TileBounds& GetBounds() const { return m_bounds; }
        const sf::Vector3i& GetGridCoords() const { return m_gridCoords; }
};
