#include <math.h>
#include "Math.h"
#include <iostream>
#define GLOBALTILESIZE 96

float Math::Length(const sf::Vector2f& v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f Math::Normalize(const sf::Vector2f& v)
{
    float len = Length(v);
    if (len != 0.0f)
        return { v.x / len, v.y / len};
    
    std::cout << "Dividing by 0 Math.h" << std::endl;
    return { 0.f, 0.f };
}

sf::Vector2f Math::Velocity(sf::Vector2f pos, sf::Vector2f prePos, float friction)
{
    return (pos - prePos) * friction;
}

float Math::CalcScale(sf::Vector2f tileSize)
{
	float defaultSize = GLOBALTILESIZE;

	float scale;

	int maxDimension = std::max(tileSize.x, tileSize.y);

	float scaleFactor = defaultSize / maxDimension;
	scale = scaleFactor;

    if (scale < 0)
    {
        std::cout << "Negative Scale" << std::endl;
        return 1.f;
    }

	return scale;
}

sf::Vector2f Math::IsoTransform(int x, int y, int z, sf::Vector2f tileSize)
{
    float isoX = (x - y) * (tileSize.x / 2.f);
    float isoY = (x + y) * (tileSize.y / 2.f) - z * tileSize.y;

    return {isoX, isoY};
}
