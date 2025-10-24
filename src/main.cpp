#include <iostream>
#include <memory>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

#include "Tile.h"
#include "Player.h"

#include "Item.h"
#include "DrawIso.h"
#include "Music.h"
#include "Background.h"
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
    float gravity = -15.f;
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

    Background bg;
    bg.Load("assets/textures/background/background.png", 10, {1280, 720});

    Music music;
    //music.Load();

    Grid grid(sf::Vector2f(windowSize), gridOffset, cellSize);
    
    TileMap map("assets/maps/map2.txt", cellSize, mapOffset);

    FrameRate fr;
    SheetManager::Load();

    Player p1(gridOffset, cellSize);

    std::unique_ptr<Item> item;

	//-----GAME LOOP-----
    sf::Mouse mouse;
	
    float fixedDt = 1.0f / fps; 
    float accumulator = 0.f;

    float loopRate = 0.1f; 
    float loopAcc = 0.f;
	sf::Clock clock;

    bool start = false;

	while (window.isOpen())
	{	
		double deltaTime = clock.restart().asSeconds();
        accumulator += deltaTime;

        loopAcc += deltaTime;

		//-----UPDATE-----

        //-----UPDATE KEYPRESSES-----

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
            else if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                p1.m_gridPos = sf::Vector3f(5.f, 2.f, 5.f);
                p1.m_prevPos = p1.m_gridPos;
                p1.m_vel.y = 0.f;
                p1.isJumping = true;
                start = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                map.Reset();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            {
                item.reset();
                int randX = std::rand() % 10;
                int randZ = std::rand() % 10;

                item = std::make_unique<Item>(cellSize, sf::Vector3i(randX, 1, randZ), SheetID::Item, gridOffset, 1);
            }

		}

        if (loopAcc >= loopRate && start)
        {
            bool empty = true;

            std::vector<CubeTile*> allTiles = map.GetAllTiles();
            int n = allTiles.size();

            int randInt = std::rand() % n;
            
            for (int i = 0; i < n; i++)
            {
                if (allTiles[i]->m_tileId && allTiles[i]->m_tileId != 2 && allTiles[i]->m_tileId != 3 && allTiles[i]->m_tileId != 4)
                {
                    empty = false;
                    break;
                }
            }

            if (!empty)
            {
                while (allTiles[randInt]->m_tileId != 1) randInt = std::rand() % n;
                allTiles[randInt]->m_decay = true;
            }

            loopAcc = 0.f;
        }
        
        while (accumulator >= fixedDt)
        {
            sf::Vector2i mousePos = mouse.getPosition(window);

            if (start)
            {
                p1.Update(deltaTime, gravity, friction);
                if (item)
                    item->Update(deltaTime);
            }

            if (item && Collision::LineHitsGrid(p1.GetFeetLine(), item->m_gridPos))
            {
                p1.Rescue();
                item.reset();
                map.Reset();
            }

            bg.Update(deltaTime);
            fr.Update(deltaTime, p1.m_gridPos, mousePos);
            
            std::vector<CubeTile*> allTiles = map.GetAllTiles();
            std::vector<CubeTile*> nearbyTiles = Collision::BroadPhase(allTiles, p1);

            if (Collision::TileUnder(p1.m_gridPos, nearbyTiles))
                p1.showShadow = true;
            else
                p1.showShadow = false;

            if (item)
            {
                sf::Vector3f itemGrid = sf::Vector3f
                    (
                     static_cast<float>(item->m_gridPos.x),
                     static_cast<float>(item->m_gridPos.y),
                     static_cast<float>(item->m_gridPos.z)
                    );

                if (Collision::TileUnder(itemGrid, allTiles))
                    item->showShadow = true;
                else
                    item->showShadow = false;
            }

            for (auto* t : allTiles)
            {
                t->Update(deltaTime);
            }

            Collision::Resolve(p1, nearbyTiles);

            accumulator -= fixedDt;
        }
        
        //-----UPDATE-----

        //-----DRAW-----
        
        window.clear(sf::Color::White);
        bg.Draw(window);
        fr.Draw(window);

        //grid.Draw(window);

        std::vector<CubeTile*> allTiles = map.GetAllTiles();

        if (start)
            DrawIso::DrawAll(allTiles, p1, item.get(), window);
        else
            map.Draw(window);

		window.display();

		//-----DRAW-----

	}

	return 0;
}
