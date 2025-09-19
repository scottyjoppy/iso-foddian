#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Grid
{
	private:
        sf::Vector2f m_gridSize;
        sf::Vector2f m_pos;
        sf::Vector2i m_cellSize;
        sf::Color m_color;
        sf::Vector2f m_scale;

        sf::VertexArray m_xLines;
        sf::VertexArray m_yLines;
        sf::VertexArray m_vLines;

	public:
		Grid (const sf::Vector2f& gridSize, const sf::Vector2f& pos, const sf::Vector2f& cellSize);
		~Grid();

		void Initialize();
		void Draw(sf::RenderWindow& window);
};	
