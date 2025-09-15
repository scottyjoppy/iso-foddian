#include "Grid.h"
#include <iostream>

Grid::Grid (const sf::Vector2f& gridSize, const sf::Vector2f& pos, const sf::Vector2f& cellSize) :
    m_gridSize(gridSize), m_pos(pos), m_cellSize(cellSize), m_color(sf::Color::Black)
{
}

Grid::~Grid()
{
}

void Grid::Initialize()
{
    m_xLines.setPrimitiveType(sf::Lines);
    for (int x = 0; x <= m_gridSize.x; x++)
    {
        sf::Vector2f start = m_pos + sf::Vector2f(x * m_cellSize.x / 2, x * m_cellSize.y / 2);
        sf::Vector2f end = m_pos + sf::Vector2f((x - m_gridSize.y) * m_cellSize.x / 2, (x + m_gridSize.y) * m_cellSize.y / 2);
        m_xLines.append(sf::Vertex(start, m_color));
        m_xLines.append(sf::Vertex(end, m_color));
    }

    m_yLines.setPrimitiveType(sf::Lines);
    for (int y = 0; y <= m_gridSize.y; y++)
    {
        sf::Vector2f start = m_pos + sf::Vector2f(-y * m_cellSize.x / 2, y * m_cellSize.y / 2);
        sf::Vector2f end = m_pos + sf::Vector2f((m_gridSize.x - y) * m_cellSize.x / 2, (m_gridSize.x + y) * m_cellSize.y / 2);
        m_yLines.append(sf::Vertex(start, m_color));
        m_yLines.append(sf::Vertex(end, m_color));
    }

    m_vLines.setPrimitiveType(sf::Lines);
    for (int x = 1; x <= m_gridSize.x; x++)
    {
        for (int y = 1; y < m_gridSize.y; y++)
        {
            sf::Vector2f pos = m_pos + sf::Vector2f((x - y) * m_cellSize.x / 2, (x + y) * m_cellSize.y / 2);
            sf::Vector2f top = pos + sf::Vector2f(0.f, -m_cellSize.y);

            m_vLines.append(sf::Vertex(pos, m_color));
            m_vLines.append(sf::Vertex(top, m_color));
        }
    }
}
	
void Grid::Draw(sf::RenderWindow& window)
{
    window.draw(m_xLines);
    window.draw(m_yLines);
    window.draw(m_vLines);
}
