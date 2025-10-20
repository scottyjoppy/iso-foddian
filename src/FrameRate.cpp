#include "FrameRate.h"
#include <iostream>
#include <sstream>
#include <iomanip>

FrameRate::FrameRate() :
	timer(0)
{
    Initialize();
    Load();
}

FrameRate::~FrameRate()
{
}

void FrameRate::Initialize()
{
}

void FrameRate::Load()
{
	if (font.loadFromFile("assets/fonts/consola.ttf"))
	{
        std::cout << "Loading FrameRate text" << std::endl;
		frameRateText.setFont(font);
        frameRateText.setFillColor(sf::Color::White);
	}
}

void FrameRate::Update(double deltaTime, sf::Vector3f gridPos, sf::Vector2i mousePos)
{
	timer += deltaTime;
    if (timer >= 0.1)
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) 
           << gridPos.x << " " << gridPos.y << " " << gridPos.z;
        
        frameRateText.setString
            (
                "FPS: " + 
                std::to_string((int)(1.0 / deltaTime)) + 
                " frameTime: " + std::to_string(deltaTime * 1000.0) + "\n" +
                "PlayerPos: " + ss.str() + "\n" +
                "MousePos: " + std::to_string(mousePos.x) + " " + std::to_string(mousePos.y)
            );
        timer = 0;
    }
}

void FrameRate::Draw(sf::RenderWindow& window)
{
	window.draw(frameRateText);
}
