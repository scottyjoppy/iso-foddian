#include <iostream>
#include <cmath>

#include "SheetLoader.h"
#include "Player.h"
#include "Math.h"

Player::Player(const sf::Vector2f& mapOffset) :
    // Size
    m_tileSize(16.f, 16.f),
    m_scale(1.f),
    // Position
    m_gridPos(0.f, 0.f, 0.f),
    m_currPos(m_gridPos),
    m_prevPos(m_gridPos),
    m_vel(0.f, 0.f, 0.f),
    // Movement
    m_playerSpeed(5.f),
    m_jumpInitVel(5.f),
    // Timers
    moveRate(0.2f),
    textureTimer(0.f),
    sheetIdx(0),
    posTimer(0.f),
    posRate(0.5f),
    // Bools
    isJumping(true),
    m_mapOffset(mapOffset)
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
    m_mapPos = Math::IsoTransform(m_gridPos, m_tileSize * m_scale) + m_mapOffset;
    m_tileSize *= m_scale;


    m_shadow.setRadius(m_tileSize.x / 4);
    m_shadow.setFillColor(sf::Color(0, 0, 0, 128));
    m_shadow.setOrigin(-m_tileSize.x / 4.5f, -m_tileSize.y * 1.6f);
    m_shadow.setScale(1.f, 0.5f);

    m_shadow.setPosition(m_mapPos.x, m_mapPos.y);
    m_sprite.setPosition(m_mapPos.x, m_mapPos.y);

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

    sf::Vector3f inputMove(0.f, 0.f, 0.f);

    bool up    = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool down  = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool left  = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    // Count how many directions are pressed
    int pressedCount = up + down + left + right;

    if (pressedCount == 1)
    {
        // --- SINGLE KEY: move in screen-space directions ---
        if (right) { inputMove.x += 1; inputMove.z += -1; } // screen right
        if (left)  { inputMove.x += -1; inputMove.z += 1; } // screen left
        if (up)    { inputMove.x += -1; inputMove.z += -1; }  // screen up
        if (down)  { inputMove.x += 1; inputMove.z += 1; }// screen down
    }
    else if (pressedCount == 2)
    {
        // --- TWO KEYS: move along grid axes ---
        if (up && right)   { inputMove.z += -1; inputMove.x += 0.33f; }   // +X grid
        if (up && left)    { inputMove.x += -1; inputMove.z += 0.33f; }   // +Z grid
        if (down && left)  { inputMove.z += 1; inputMove.x += -0.33f; }  // -X grid
        if (down && right) { inputMove.x += 1; inputMove.z += -0.33f; }  // -Z grid
    }

    // Normalize (so diagonals aren’t faster)
    if (inputMove.x != 0.f || inputMove.z != 0.f)
    {
        float len = std::sqrt(inputMove.x * inputMove.x + inputMove.z * inputMove.z);
        inputMove.x /= len;
        inputMove.z /= len;
    }

    // Apply movement
    m_gridPos.x += inputMove.x * m_playerSpeed * deltaTime;
    m_gridPos.z += inputMove.z * m_playerSpeed * deltaTime;

    // Movement Y
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) 
    {
        isJumping = true;
        m_vel.y = m_jumpInitVel;
    }

    if (isJumping)
   {
        m_vel.y += acc * deltaTime;
        m_gridPos.y += m_vel.y * deltaTime;

        if (m_gridPos.y <= 0.f)
        {
            m_gridPos.y = 0.f;
            m_vel.y = 0.f;
            isJumping = false;
        }
    }

    sf::Vector2f groundPos = Math::IsoToScreen(sf::Vector3f(m_gridPos.x, 0.f, m_gridPos.z), m_tileSize) + m_mapOffset - sf::Vector2f(m_tileSize.x / 2, m_tileSize.y);

    m_mapPos = Math::IsoToScreen(m_gridPos, m_tileSize) + m_mapOffset - sf::Vector2f(m_tileSize.x / 2, m_tileSize.y);
    
    m_shadow.setPosition(m_mapPos.x, groundPos.y);
    m_sprite.setPosition(m_mapPos.x, m_mapPos.y);
    m_bounds.setPosition(m_sprite.getPosition().x + m_bounds.getSize().x / 3.4f, m_sprite.getPosition().y + 10.f);

    //std::cout << m_gridPos.x << " " << m_gridPos.y << " " << m_gridPos.z << std::endl;
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
