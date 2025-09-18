#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

class StaticObj
{
    public:
        sf::Vector3f m_pos;
        sf::Vector2f m_objSize;

    public:
        StaticObj(sf::Vector3f pos, sf::Vector2f objSize) :
            m_pos(pos), m_objSize(objSize)
        ~StaticObj();
};
