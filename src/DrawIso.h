#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.h"
#include "CubeTile.h"

struct Drawable
{
    sf::Sprite* sprite;
    sf::Vector3f depth;
};

class DrawIso
{
	public:
        static void DrawAll(std::vector<CubeTile*>& tiles, Player& p, sf::RenderWindow& window);
};
