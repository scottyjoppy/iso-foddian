#include <iostream>
#include <cmath>

#include "SheetLoader.h"
#include "Player.h"
#include "Math.h"

Player::Player(const sf::Vector2f& mapOffset, const sf::Vector2f& cellSize) :
    // Size
    m_tileSize(cellSize),
    m_scaledTileSize(m_tileSize),
    m_scaledPlayerSize(m_playerSize),
    m_tileScale(1.f),
    m_playerScale(1.f),
    // Position
    m_gridPos(0.f, 0.f, 0.f),
    m_currPos(m_gridPos),
    m_prevPos(m_gridPos),
    m_vel(0.f, 0.f, 0.f),
    // Movement
    m_playerSpeed(5.f),
    m_jumpInitVel(10.f),
    // Timers
    moveRate(0.2f),
    textureTimer(0.f),
    sheetIdx(0),
    posTimer(0.f),
    posRate(0.5f),
    // Bools
    isJumping(false),
    m_mapOffset(mapOffset)
{
    Initialize();
    Load();
    SetBounds();
}

Player::~Player()
{
}

void Player::Initialize()
{
    std::cout << "Initializing Player" << std::endl;
    m_tileScale = Math::CalcScale(m_tileSize);
    m_scaledTileSize = m_tileSize * m_tileScale;
    m_mapPos = Math::IsoTransform(m_gridPos, m_scaledTileSize) + m_mapOffset;

    m_shadow.setRadius(m_scaledTileSize.x / 4);
    m_shadow.setFillColor(sf::Color(0, 0, 0, 128));
    m_shadow.setOrigin(-m_scaledTileSize.x / 4.5f, -m_scaledTileSize.y * 0.5f);
    m_shadow.setScale(1.f, 0.5f);

    m_shadow.setPosition(m_mapPos.x, m_mapPos.y);
    m_sprite.setPosition(m_mapPos.x, m_mapPos.y);

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

    float step = 1;

    if (pressedCount == 1)
    {
        // --- SINGLE KEY: move in screen-space directions ---
        if (right) { inputMove.x += step; inputMove.z += -step; } // screen right
        if (left)  { inputMove.x += -step; inputMove.z += step; } // screen left
        if (up)    { inputMove.x += -step; inputMove.z += -step; }  // screen up
        if (down)  { inputMove.x += step; inputMove.z += step; }// screen down
    }
    else if (pressedCount == 2)
    {
        // --- TWO KEYS: move along grid axes ---
        if (up && right)   { inputMove.z += -step * 0.33f; }   // +X grid
        if (up && left)    { inputMove.x += -step * 0.33f; }   // +Z grid
        if (down && left)  { inputMove.z += step * 0.33f; }  // -X grid
        if (down && right) { inputMove.x += step * 0.33f; }  // -Z grid
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

    m_vel.y += acc * deltaTime;
    m_gridPos.y += m_vel.y * deltaTime;
   


    m_mapPos = Math::IsoTransform(m_gridPos, m_scaledTileSize) + m_mapOffset;
    sf::Vector2f groundPos = Math::IsoTransform(sf::Vector3f(m_gridPos.x, 1.f, m_gridPos.z), m_scaledTileSize) + m_mapOffset;

    m_shadow.setPosition(m_mapPos.x, groundPos.y);
    m_sprite.setPosition(m_mapPos.x, m_mapPos.y);
    
    sf::FloatRect sprGb = m_sprite.getGlobalBounds();
    float feetX = sprGb.left + sprGb.width * 0.5f;
    float feetY = sprGb.top + sprGb.height;
    m_bounds.setPosition(feetX, feetY);
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
    m_playerSize = sheet.m_spriteSize;
    m_playerScale = Math::CalcScale(m_playerSize);
    m_scaledPlayerSize = m_playerSize * m_playerScale;
    m_sprite.setScale(m_playerScale, m_playerScale);
    m_sprite.setOrigin(sheet.m_origin);
}

void Player::SetBounds()
{
    m_boundsSize = { m_scaledPlayerSize.x * 0.5f, m_scaledPlayerSize.y * 0.9f };

    m_bounds.setSize(m_boundsSize);
    m_bounds.setOrigin(m_boundsSize.x * 0.5f, m_boundsSize.y);
    m_bounds.setFillColor(sf::Color::Transparent);
    m_bounds.setOutlineColor(sf::Color::Red);
    m_bounds.setOutlineThickness(1.f);
}
