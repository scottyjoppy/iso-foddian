#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

#include "Player.h"
#include "CubeTile.h"


struct Line
{
    sf::Vector2f p1;
    sf::Vector2f p2;
};

class Collision
{
    public:
        static bool LineLine(const Line& l1, const Line& l2);
        static bool LineRect(const Line& line, const sf::FloatRect& rect);
        static bool LineHitsGrid(const std::pair<sf::Vector3f, sf::Vector3f>& feetLine, const sf::Vector3i& gridPos);
        static bool TileUnder(const sf::Vector3f& obj, const std::vector<CubeTile*>& tiles);
        static bool NearTiles(const sf::Vector3f& obj1, const sf::Vector3f& obj2, const float tolerance = 1.5f);
        static void Resolve(Player& p, const std::vector<CubeTile*>& tiles);
        static std::vector<CubeTile*> BroadPhase(std::vector<CubeTile*>& allTiles, Player& p);
};
