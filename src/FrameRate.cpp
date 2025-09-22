#include "FrameRate.h"
#include <iostream>

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
        frameRateText.setFillColor(sf::Color::Black);
	}
}

void FrameRate::Update(double deltaTime)
{
	timer += deltaTime;

	if (timer >= 0.1)
	{
		frameRateText.setString
			(
				"FPS: " + 
				std::to_string((int)(1.0 / deltaTime)) + 
				" frameTime: " + std::to_string(deltaTime * 1000.0)
			);
		timer = 0;
	}
}

void FrameRate::Draw(sf::RenderWindow& window)
{
	window.draw(frameRateText);
}
