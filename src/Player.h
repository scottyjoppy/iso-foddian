#pragma once
#include <SFML/Graphics.hpp>
#include "SheetLoader.h"
#include "SheetManager.h"

class Player
{
	private:
		sf::Texture m_texture;
        sf::Sprite m_sprite;

        sf::Vector2i m_tileSize;
        sf::Vector2f m_scale;
        sf::Vector2f m_pos;

		float m_playerSpeed;
        int index;
        float movementRate;
        float timer;
        SheetID activeSheetID;

	public:
		Player();
		~Player();

		void Initialize();
		void Load();
		void Update(float deltaTime);
		void Draw(sf::RenderWindow& window);	

        void SetActiveSheet(SheetID id);
};
