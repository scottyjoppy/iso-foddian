#pragma once

#include <vector>
#include <string>
#include "Frame.h"

class SheetLoader
{
    public:
        sf::Vector2i m_tileSize;
        sf::Vector2f m_spriteSize;
        sf::Vector2i m_index;
        sf::Vector2u m_sheetSize;
        float m_scale;

		sf::Texture m_texture;
		sf::RectangleShape m_boundingRectangle;
        sf::Vector2f m_origin;

        std::vector <Frame> frames;

        std::string m_fileDir;

    public:
        SheetLoader(std::string fileDir, sf::Vector2i tileSize, sf::Vector2i spriteSize, sf::Vector2f origin = {0.f, 0.f});
        ~SheetLoader();

        void Initialize();
        void Load();
};
