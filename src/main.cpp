#include <iostream>
#include <SFML/Graphics.hpp>

#include "Tile.h"
#include "Player.h"

#include "TileMap.h"
#include "SheetManager.h"
#include "Grid.h"
#include "FrameRate.h"
#include "Math.h"
#include "Collision.h"


sf::Vector2u windowSize(1920, 1080);


int main()
{
    // MAGIC
    float gravity = -9.8f;
    float bounce = 0.9f;
    float friction = 0.999f;
    float fps = 60.f;

    sf::Vector2f cellSize = {32, 16};
    sf::Vector2f scaledCellSize = cellSize * Math::CalcScale(cellSize);
    sf::Vector2f gridOffset(windowSize.x / 2.f, windowSize.y / 3.f);
    sf::Vector2f mapOffset(windowSize.x / 2.f - scaledCellSize.x / 2, windowSize.y / 3.f);
    float depth = 0.f;

	//-----INITIALIZE WINDOW-----

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Iso Platformer", sf::Style::Default, settings);
	window.setFramerateLimit(fps);

	//-----INITIALIZE GAME-----
    SheetManager::Load();

    Collision::m_g = gravity;
    Collision::m_b = bounce;
    Collision::m_f = friction;

    Grid grid(sf::Vector2f(windowSize), gridOffset, cellSize);
    
    TileMap map("assets/maps/map2.txt", cellSize, mapOffset);

    FrameRate fr;
    SheetManager::Load();

    Player p1(mapOffset, cellSize);

	//-----GAME LOOP-----
	
    float fixedDt = 1.0f / fps; 
    float accumulator = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{	
		double deltaTime = clock.restart().asSeconds();
        accumulator += deltaTime;

		//-----UPDATE-----
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
            else if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                p1.m_gridPos = sf::Vector3f(5.f, 5.f, 5.f);
                p1.m_prevPos = p1.m_gridPos;
                p1.isJumping = true;
            }

		}

        while (accumulator >= fixedDt)
        {
            p1.Update(deltaTime, gravity, friction);
            fr.Update(deltaTime, p1.m_gridPos);
            
            std::vector<CubeTile*> allTiles = map.GetAllTiles();
            for (auto& t : allTiles)
            {
                float dist = Math::GetDist(p1.m_gridPos, sf::Vector3f
                        (
                         static_cast<float>(t->m_gridCoords.x),
                         static_cast<float>(t->m_gridCoords.y),
                         static_cast<float>(t->m_gridCoords.z)
                        ));
                if (dist <= 2)
                    t->m_bounds.m_debugColorsEnabled = false;
                else
                    t->m_bounds.m_debugColorsEnabled = true;
                t->Update(deltaTime);
            }

            accumulator -= fixedDt;
        }

        
        //-----UPDATE-----

        //-----DRAW-----
        
        window.clear(sf::Color::White);

        grid.Draw(window);
        fr.Draw(window);
        map.Draw(window);
        p1.Draw(window);

		window.display();

		//-----DRAW-----

	}

	return 0;
}
