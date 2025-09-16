#pragma once
#include <SFML/Graphics.hpp>

class Player
{
	private:
		sf::Texture m_texture;

		sf::RectangleShape m_boundingRectangle;
		sf::Vector2i m_size;

		float m_playerSpeed;

		int m_tileWidth;
		int m_tileHeight;
		sf::Vector2f m_scale;

	public:
		sf::Sprite m_sprite;

	public:
		Player();
		~Player();
		void Initialize();
		void Load();
		void Update();
		void Draw(sf::RenderWindow& window);	
};
