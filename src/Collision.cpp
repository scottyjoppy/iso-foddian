#include <math.h>
#include <iostream>

#include "Math.h"
#include "Collision.h"

void Collision::CircleVsWindow(sf::Vector2f& pos, sf::Vector2f& prePos, sf::Vector2f& v, const float r, const sf::RenderWindow& window)
{
    sf::Vector2u winS = window.getSize();
    if (pos.x > winS.x - r)
    {
        pos.x = winS.x - r;
        prePos.x = pos.x + v.x * m_b;
    }
    else if (pos.x < r)
    {
        pos.x = r;
        prePos.x = pos.x + v.x * m_b;
    }

    if (pos.y > winS.y - r)
    {
        pos.y = winS.y - r;
        prePos.y = pos.y + v.y * m_b;
    }
    else if (pos.y < r)
    {
        pos.y = r;
        prePos.y = pos.y + v.y * m_b;
    }
}
