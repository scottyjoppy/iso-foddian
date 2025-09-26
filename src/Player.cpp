#include <iostream>
#include <cmath>

#include "SheetLoader.h"
#include "Player.h"
#include "Math.h"

Player::Player() :
    // Size
    m_tileSize(16.f, 16.f),
    m_scale(1.f),
    // Position
    m_spritePos(500, 0, 500),
    m_currPos(m_spritePos),
    m_prevPos(m_spritePos),
    m_vel(0.f, 0.f, 0.f),
    // Movement
    m_moveStep(10.f, 10.f, 10.f),
    m_playerSpeed(500.f),
    m_jumpInitVel(500.f),
    // Timers
    moveRate(0.2f),
    textureTimer(0.f),
    sheetIdx(0),
    posTimer(0.f),
    posRate(0.5f),
    // Bools
    isJumping(true)
{
    Initialize();
    Load();
}

Player::~Player()
{
}

void Player::Initialize()
{
    std::cout << "Initializing Player" << std::endl;
    m_scale = Math::CalcScale(m_tileSize);
    m_tileSize *= m_scale;

    m_shadow.setRadius(m_tileSize.x / 4);
    m_shadow.setFillColor(sf::Color(0, 0, 0, 128));
    m_shadow.setOrigin(-m_tileSize.x / 4.5f, -m_tileSize.y * 1.6f);
    m_shadow.setScale(1.f, 0.5f);

    m_shadow.setPosition(m_spritePos.x, m_spritePos.z);
    m_sprite.setPosition(m_spritePos.x, -m_spritePos.y + m_spritePos.z);

    m_bounds.setOutlineColor(sf::Color::Black);
    m_bounds.setOutlineThickness(1);
    m_bounds.setFillColor(sf::Color(255, 255, 0, 80));
    m_bounds.setSize(sf::Vector2f(m_tileSize.x * 0.6f, m_tileSize.y - 10.f));
}

void Player::Load()
{
    std::cout << "Loading sheet into Player" << std::endl;
    SetActiveSheet(SheetID::PlayerIdle);
}

void Player::Update(float deltaTime, float acc, float friction)
{
    // Set sheet to activeSheet
    SheetLoader& sheet = SheetManager::Get(activeSheetID);

    // Loop through sheet on a timer
    textureTimer += deltaTime;
    if (textureTimer > moveRate)
    {
        m_sprite.setTextureRect(sheet.frames[sheetIdx % sheet.frames.size()].rect);
        textureTimer = 0;
        sheetIdx++;
    }

    // Sheet set to walking when moving
    if (
         !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
         !sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
         !sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
         !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
         activeSheetID != SheetID::PlayerIdle
        )
        SetActiveSheet(SheetID::PlayerIdle);
    else if (
             (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::S)) &&
             activeSheetID != SheetID::PlayerWalk
            )
        SetActiveSheet(SheetID::PlayerWalk);

    // Handle movement X Z
    sf::Vector3f inputMove(0.f, 0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) inputMove.x -= m_moveStep.x;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) inputMove.x += m_moveStep.x;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) inputMove.z -= m_moveStep.z;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) inputMove.z += m_moveStep.z;

    // Normalize diagonal movement
    sf::Vector2f xz(inputMove.x, inputMove.z);
    if (xz.x != 0.f || xz.y != 0.f)
    {
        float len = std::sqrt(xz.x*xz.x + xz.y*xz.y);

        xz /= len;

        inputMove.x = xz.x;
        inputMove.z = xz.y * 0.5f;
    }

    m_spritePos.x += inputMove.x * m_playerSpeed * deltaTime;
    m_spritePos.z += inputMove.z * m_playerSpeed * deltaTime;

    // Movement Y
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) 
    {
        isJumping = true;
        m_prevPos.y = m_spritePos.y;
        m_spritePos.y += m_jumpInitVel * deltaTime;
    }

    if (isJumping)
    {
        float yNew = 2.f * m_spritePos.y - m_prevPos.y + acc * deltaTime * deltaTime;
        m_prevPos.y = m_spritePos.y;
        m_spritePos.y = yNew;
    }

    if (m_spritePos.y <= 0.f)
    {
        m_spritePos.y = 0.f;
        isJumping = false;
    }
    
    m_shadow.setPosition(m_spritePos.x, m_spritePos.z);
    m_sprite.setPosition(m_spritePos.x, -m_spritePos.y + m_spritePos.z);
    m_bounds.setPosition(m_sprite.getPosition().x + m_bounds.getSize().x / 3.4f, m_sprite.getPosition().y + 10.f);

//    posTimer += deltaTime; 
//    if (posTimer > posRate)
//    {
//        std::cout << "X::" << m_spritePos.x << " " << "Y::" << m_spritePos.y << " " << "Z::" << m_spritePos.x << std::endl;
//        posTimer = 0;
//    }
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(m_shadow);
    window.draw(m_sprite);
    window.draw(m_bounds);
}

void Player::SetActiveSheet(SheetID id)
{
    activeSheetID = id;
    sheetIdx = 0;

    auto& sheet = SheetManager::Get(id);
    m_texture = &sheet.m_texture;
    m_sprite.setTexture(*m_texture);
    m_sprite.setTextureRect(sheet.frames[0].rect);
    m_sprite.setScale(m_scale, m_scale);
}
