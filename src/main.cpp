#include <iostream>
#include <SFML/Graphics.hpp>

#include "Tile.h"
#include "Player.h"

#include "SheetManager.h"
#include "Grid.h"
#include "FrameRate.h"
#include "Math.h"
#include "Collision.h"


sf::Vector2u windowSize(1920, 1080);


int main()
{
    // MAGIC
    float gravity = -9.8f * 100.f;
    float bounce = 0.9f;
    float friction = 0.999f;
    float fps = 60.f;

    sf::Vector2i cellSize = {32, 16};
    float depth = 0.f;

	//-----INITIALIZE WINDOW-----

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Iso Platformer", sf::Style::Default, settings);
	window.setFramerateLimit(fps);

	//-----INITIALIZE GAME-----

    Collision::m_g = gravity;
    Collision::m_b = bounce;
    Collision::m_f = friction;

    Grid grid(sf::Vector2f(windowSize), sf::Vector2f(windowSize.x / 2, windowSize.y / 3), cellSize);
    
    Tile tiles(sf::Vector2f(cellSize.x, cellSize.y), sf::Vector3f(500, 500, 500));

    FrameRate fr;
    SheetManager::Load();

    Player p1;

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
                p1.m_spritePos = sf::Vector3f(500, 500, 500);
                p1.m_prevPos = p1.m_spritePos;
                p1.isJumping = true;
            }

		}

        while (accumulator >= fixedDt)
        {
            fr.Update(deltaTime);
            p1.Update(deltaTime, gravity, friction);

            accumulator -= fixedDt;
        }

        
        //-----UPDATE-----

        //-----DRAW-----
        
        window.clear(sf::Color::White);

        grid.Draw(window);
        fr.Draw(window);
        tiles.Draw(window);
        p1.Draw(window);

		window.display();

		//-----DRAW-----

	}

	return 0;
}
