#include <iostream>
#include <SFML/Graphics.hpp>

#include "Tile.h"
#include "Player.h"

#include "Grid.h"
#include "FrameRate.h"
#include "Math.h"
#include "Collision.h"


sf::Vector2u windowSize(1920, 1080);


int main()
{
    // MAGIC
    float gravity = 0.5f;
    float bounce = 0.9f;
    float friction = 0.999f;
    float fps = 60.f;

    sf::Vector2f cellSize = {32.0f, 16.f};
    float scale = 2.f;
    float depth = 32.f;

	//-----INITIALIZE WINDOW-----

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Iso Platformer", sf::Style::Default, settings);
	window.setFramerateLimit(fps);

	//-----INITIALIZE GAME-----


    Grid grid(sf::Vector2f(windowSize), sf::Vector2f(windowSize.x / 2, -cellSize.y), cellSize, scale);
    grid.Initialize();

    FrameRate fr;
    fr.Initialize();
    fr.Load();

    Player p1;

    Collision::m_g = gravity;
    Collision::m_b = bounce;
    Collision::m_f = friction;

    std::vector <Tile> tiles;
    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 20; y++)
        {
            tiles.emplace_back(cellSize, sf::Vector2i(x, y), sf::Vector2f(windowSize.x / 2, 0.f), depth, scale);
        }
    }

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
		}

        while (accumulator >= fixedDt)
        {
            fr.Update(deltaTime);

            accumulator -= fixedDt;
        }

        
        //-----UPDATE-----

        //-----DRAW-----
        
        window.clear(sf::Color::White);

        grid.Draw(window);
        fr.Draw(window);
        for (auto& t : tiles) t.Draw(window);
        p1.Draw(window);

		window.display();

		//-----DRAW-----

	}

	return 0;
}
