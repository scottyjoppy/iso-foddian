#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.h"
#include "CubeTile.h"

enum class DrawableType { Player, CubeTile };

struct Drawable
{
    DrawableType type;
    void* entity;
    sf::Vector3f depth;

    void Draw(sf::RenderWindow& window) const {
        switch (type) {
            case DrawableType::Player:
                static_cast<Player*>(entity)->Draw(window);
                break;
            case DrawableType::CubeTile:
                static_cast<CubeTile*>(entity)->Draw(window);
                break;
        }
    }
};

class DrawIso
{
	public:
        static void DrawAll(std::vector<CubeTile*>& tiles, Player& p, sf::RenderWindow& window);
};
