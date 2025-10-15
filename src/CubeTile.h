#pragma once
#include <SFML/Graphics.hpp>

#include "TileBounds.h"

class CubeTile
{
    public:
        sf::Sprite m_sprite;
        sf::Vector3i m_gridCoords;
        sf::Vector2f m_tileSize;
        sf::Vector2f m_mapPos;
        sf::Vector2f m_mapOffset;
        int m_logicalHeight;
        float m_scale;

        float m_cubeHeight;

        TileBounds m_bounds;
        sf::RectangleShape m_cubeBounds;
        sf::FloatRect m_boundBox;

        int m_tileId;

    public:
        CubeTile(const sf::Vector2f& tileSize, sf::Vector3i gridCoords, int tileId, const sf::Vector2f& mapOffset, int logicalHeight);
        ~CubeTile();

        void Initialize();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        void SetTile(int tileId);

        const TileBounds& GetBounds() const { return m_bounds; }
        const sf::Vector3i& GetGridCoords() const { return m_gridCoords; }
};
