#pragma once
#include <SFML/Graphics.hpp>
#include "SheetLoader.h"
#include "SheetManager.h"

class Player
{
	private:
        sf::RectangleShape m_rectBounds;
        SheetID activeSheetID;
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        sf::Vector2f m_tileSize;
        float m_scale;

        sf::Vector3f m_spritePos;
        sf::Vector3f m_currPos;
        sf::Vector3f m_prevPos;
        sf::Vector3f m_vel;

        sf::Vector3f m_moveStep;
        float m_playerSpeed;
        float m_jumpInitVel;

        float moveRate;
        float textureTimer;
        int sheetIdx;

        bool isJumping;

        sf::CircleShape m_shadow;

	public:
		Player();
		~Player();

		void Initialize();
		void Load();
		void Update(float deltaTime, float acc, float friction);
		void Draw(sf::RenderWindow& window);	

        void SetActiveSheet(SheetID id);
};
