#pragma once

#include <SFML/Graphics.hpp>

class Collision
{
    public:
        inline static float m_g = 0.f;
        inline static float m_b = 0.f;
        inline static float m_f = 0.f;

    public:
        static void CircleVsWindow(sf::Vector2f& pos, sf::Vector2f& prePos, sf::Vector2f& v, const float r, const sf::RenderWindow& window);
};
