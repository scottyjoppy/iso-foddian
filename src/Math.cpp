#include <math.h>
#include "Math.h"
#include <iostream>

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

