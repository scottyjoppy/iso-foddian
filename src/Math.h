#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Math
{
	public:
		static float Length(const sf::Vector2f& v);
        static sf::Vector2f Normalize(const sf::Vector2f& v);
        static sf::Vector2f Velocity(sf::Vector2f pos, sf::Vector2f prePos, float friction);
		static float CalcScale(sf::Vector2f tileSize);
        static sf::Vector2f IsoTransform(int x, int y, int z, sf::Vector2f tileSize);
        static float GetDist(sf::Vector3f obj1, sf::Vector3f ob2);
};
