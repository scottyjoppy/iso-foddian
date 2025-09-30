#pragma once
#include <SFML/Graphics.hpp>

class FrameRate
{
	private:
		sf::Text frameRateText;
		sf::Font font;

		float timer;
	
	public:
		FrameRate();
		~FrameRate();

		void Initialize();
		void Load();
		void Update(double deltaTime, sf::Vector3f gridPos);
		void Draw(sf::RenderWindow& window);
};
