#pragma once
#include <SFML/Graphics.hpp>

#include "SheetLoader.h"
#include "SheetManager.h"

class Tile
{
    public:
        sf::ConvexShape m_conBounds;
        SheetID activeSheetID;
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        sf::Vector2f m_tileSize;
        float m_scale;

        sf::Vector3f m_tilePos;

        int sheetIdx;

    public:
        Tile(const sf::Vector2f& tileSize, const sf::Vector3f& tilePos);
        ~Tile();

        void Initialize();
        void Load();
        void Draw(sf::RenderWindow& window);

        void SetActiveSheet(SheetID id);
};
