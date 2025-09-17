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

		sf::Texture m_texture;
		sf::RectangleShape m_boundingRectangle;

        std::vector <Frame> frames;

        std::string m_fileDir;

    public:
        SheetLoader(std::string fileDir, sf::Vector2i tileSize, sf::Vector2i spriteSize);
        ~SheetLoader();

        void Initialize();
        void Load();
};
