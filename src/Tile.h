#pragma once
#include <SFML/Graphics.hpp>

#include "SheetLoader.h"
#include "SheetManager.h"

class Tile
{
    public:
        sf::ConvexShape m_conBounds;
        SheetID activeSheetID;
        sf::Texture* m_texture;
        sf::Sprite m_sprite;

        sf::Vector2f m_tileSize;
        float m_scale;

        sf::Vector3f m_tilePos;
        sf::Vector3i m_gridCoords;
        sf::Vector2f m_mapOffset;

    public:
        Tile(const sf::Vector2f& tileSize, sf::Vector3i gridCoords, SheetID sheetID, const sf::Vector2f& mapOffset);
        ~Tile();

        void Initialize();
        void Load();
        void Draw(sf::RenderWindow& window);

        void SetActiveSheet(SheetID id);
};
