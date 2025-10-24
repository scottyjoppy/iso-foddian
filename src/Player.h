#pragma once
#include <SFML/Graphics.hpp>

#include "SheetLoader.h"
#include "SheetManager.h"

class Player
{
	public:
        sf::RectangleShape m_bounds;
        sf::Vector2f m_boundsSize;
        sf::Vector2f m_boundsOffset;

        SheetID activeSheetID;
        sf::Texture* m_texture;
        sf::Sprite m_sprite;

        sf::Vector2f m_tileSize;
        sf::Vector2f m_playerSize;
        sf::Vector2f m_scaledTileSize;
        sf::Vector2f m_scaledPlayerSize;
        float m_tileScale;
        float m_playerScale;

        sf::Vector3f m_gridPos;
        sf::Vector2f m_mapPos;
        sf::Vector3f m_currPos;
        sf::Vector3f m_prevPos;
        sf::Vector3f m_vel;

        float m_playerSpeed;
        float m_jumpInitVel;

        float sheetRate;
        float textureTimer;
        int sheetIdx;
        float posTimer;
        float posRate;

        bool isJumping;

        sf::Vector2f m_mapOffset;

        sf::CircleShape m_shadow;

        int m_sheetOffset;
        int m_lastClicked;
        bool m_wasMoving;

        bool showShadow;

        bool debugging;

	public:
		Player(const sf::Vector2f& mapOffset, const sf::Vector2f& cellSize);
		~Player();

		void Initialize();
		void Load();
		void Update(float deltaTime, float acc, float friction);
		void Draw(sf::RenderWindow& window);	

        void SetActiveSheet(SheetID id);
        void SetBounds();
        std::pair<sf::Vector3f, sf::Vector3f> GetFeetLine() const;
        void DrawFeetLine(sf::RenderWindow& window);
        void UpdateSheet(bool isMoving, float deltaTime);
        void Rescue();
};
