#pragma once
#include <SFML/Graphics.hpp>

#include "SheetManager.h"

class Item
{
    public:
        sf::Sprite m_sprite;
        sf::Vector3i m_gridPos;
        sf::Vector2f m_tileSize;
        sf::Vector2f m_mapPos;
        sf::Vector2f m_mapOffset;
        int m_logicalHeight;
        float m_scale;

        SheetID m_id;

        float m_cubeHeight;

        sf::RectangleShape m_cubeBounds;
        sf::FloatRect m_boundBox;
        int sheetIdx;
        float m_sheetRate;
        float m_sheetAcc;

        bool showShadow;

        sf::CircleShape m_shadow;

        bool debugging;

    public:
        Item(const sf::Vector2f& tileSize, sf::Vector3i gridPos, SheetID id, const sf::Vector2f& mapOffset, int logicalHeight);
        ~Item();

        void Initialize();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
        void SetTile(SheetID id);
};
