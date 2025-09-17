#include <iostream>

#include "Player.h"
#include "Math.h"

Player::Player() :
    m_playerSpeed(1.0f), 
    m_tileSize(16, 16),
    m_scale(1.f, 1.f),
    m_pos(500, 500),
    movementRate(0.25f), 
    timer(0), 
    index(0)
{
    Initialize();
    Load();
}

Player::~Player()
{
}

void Player::Initialize()
{
    m_scale = Math::CalcScale(m_tileSize);
}

void Player::Load()
{
    SheetManager::Load();
    SetActiveSheet(SheetID::PlayerIdle);
}

void Player::Update(float deltaTime)
{
    auto& sheet = SheetManager::Get(activeSheetID);

    m_pos = m_sprite.getPosition();
    timer += deltaTime;
    if (timer > movementRate && index < sheet.frames.size())
    {
        m_sprite.setTextureRect(sheet.frames[index].rect);
        timer = 0;
        index++;
    }
    else if (index >= sheet.frames.size())
        index = 0;

    if (
         !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
         !sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
         !sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
         !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
         activeSheetID != SheetID::PlayerIdle
        )
        SetActiveSheet(SheetID::PlayerIdle);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_sprite.setPosition(m_pos - sf::Vector2f(1000.f, 0.f) * m_playerSpeed * deltaTime);
        if (activeSheetID != SheetID::PlayerWalk)
            SetActiveSheet(SheetID::PlayerWalk);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_sprite.setPosition(m_pos + sf::Vector2f(1000.f, 0.f) * m_playerSpeed * deltaTime);
        if (activeSheetID != SheetID::PlayerWalk)
            SetActiveSheet(SheetID::PlayerWalk);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_sprite.setPosition(m_pos - sf::Vector2f(0.f, 1000.f) * m_playerSpeed * deltaTime);
        if (activeSheetID != SheetID::PlayerWalk)
            SetActiveSheet(SheetID::PlayerWalk);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_sprite.setPosition(m_pos + sf::Vector2f(0.f, 1000.f) * m_playerSpeed * deltaTime);
        if (activeSheetID != SheetID::PlayerWalk)
            SetActiveSheet(SheetID::PlayerWalk);
    }
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void Player::SetActiveSheet(SheetID id)
{
    activeSheetID = id;
    index = 0;

    auto& sheet = SheetManager::Get(id);
    m_texture = sheet.m_texture;
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sheet.frames[0].rect);
    m_sprite.setScale(m_scale);
}
