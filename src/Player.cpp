#include <iostream>

#include "SheetLoader.h"
#include "Player.h"
#include "Math.h"

Player::Player() :
	m_playerSpeed(1.0f), m_tileWidth(40), m_tileHeight(48)
{
    Initialize();
    Load();
}

Player::~Player()
{
}

void Player::Initialize()
{
}

void Player::Load()
{
    SheetLoader sheet
        ("assets/textures/player/walk.png",
         {80, 80},
         {16.f, 16.f}
        );
    sheet.Load();
    m_texture = sheet.m_texture;
    
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sheet.frames[0].rect);
    m_sprite.setPosition({500, 500});

}

void Player::Update()
{
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
