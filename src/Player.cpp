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
    m_gridPos(5.f, 10.f, 5.f),
    m_currPos(m_gridPos),
    m_prevPos(m_gridPos),
    m_vel(0.f, 0.f, 0.f),
    // Movement
    m_playerSpeed(5.f),
    m_jumpInitVel(7.f),
    // Timers
    sheetRate(0.09f),
    textureTimer(0.f),
    sheetIdx(0),
    posTimer(0.f),
    posRate(0.5f),
    // Bools
    isJumping(false),
    m_mapOffset(mapOffset),
    m_sheetOffset(0),
    m_wasMoving(false),

    debugging(false)
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
    m_shadow.setOrigin(m_shadow.getRadius(), -m_shadow.getRadius());
    m_shadow.setScale(1.f, 0.5f);

    m_shadow.setPosition(m_mapPos.x, m_mapPos.y);
    m_sprite.setPosition(m_mapPos.x, m_mapPos.y);

}

void Player::Load()
{
    std::cout << "Loading sheet into Player" << std::endl;
    // Start player looking down
    m_lastClicked = 3;
    SetActiveSheet(SheetID::PlayerIdle);
}

void Player::Update(float deltaTime, float acc, float friction)
{
    bool up    = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool down  = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool left  = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    sf::Vector3f inputMove(0.f, 0.f, 0.f);

    // Count how many directions are pressed
    int pressedCount = up + down + left + right;

    float step = 1;

    if (pressedCount == 1)
    {
        // --- SINGLE KEY: move in screen-space directions ---
        if (right) { inputMove.x += step; inputMove.z += -step; m_lastClicked = 0; } // screen right
        if (left)  { inputMove.x += -step; inputMove.z += step; m_lastClicked = 1; } // screen left
        if (up)    { inputMove.x += -step; inputMove.z += -step; m_lastClicked = 2; }  // screen up
        if (down)  { inputMove.x += step; inputMove.z += step; m_lastClicked = 3; }// screen down
    }
    else if (pressedCount == 2)
    {
        // --- TWO KEYS: move along grid axes ---
        if (up && right)   { inputMove.z += -step * 0.33f; m_lastClicked = 2; }   // +X grid
        if (up && left)    { inputMove.x += -step * 0.33f; m_lastClicked = 2; }   // +Z grid
        if (down && left)  { inputMove.z += step * 0.33f; m_lastClicked = 1; }  // -X grid
        if (down && right) { inputMove.x += step * 0.33f; m_lastClicked = 0; }  // -Z grid
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

    bool isMoving = (inputMove.x != 0.f || inputMove.z != 0.f);

    SheetID targetSheet = isMoving ? SheetID::PlayerWalk : SheetID::PlayerIdle;
    if (activeSheetID != targetSheet)
        SetActiveSheet(targetSheet);
    
    UpdateSheet(isMoving, deltaTime);

    // Movement Y
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_vel.y == 0.f) 
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
    if (debugging)
    {
        window.draw(m_bounds);
        DrawFeetLine(window);
    }
}

void Player::SetActiveSheet(SheetID id)
{
    activeSheetID = id;

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
    m_bounds.setOutlineColor(sf::Color::Blue);
    m_bounds.setOutlineThickness(1.f);
}

std::pair<sf::Vector3f, sf::Vector3f> Player::GetFeetLine() const
{
    float shrink = 0.25f;
    float feetY = m_gridPos.y;

    sf::Vector3f leftFoot(m_gridPos.x + shrink, feetY, m_gridPos.z + 1.f - shrink);
    sf::Vector3f rightFoot(m_gridPos.x + 1.f - shrink, feetY, m_gridPos.z + shrink);

    return { leftFoot, rightFoot };
}

void Player::DrawFeetLine(sf::RenderWindow& window)
{
    auto [leftFoot, rightFoot] = GetFeetLine();

    sf::Vertex line[] = 
    {
        sf::Vertex(Math::IsoTransform(leftFoot, m_scaledTileSize) + m_mapOffset, sf::Color::Green),
        sf::Vertex(Math::IsoTransform(rightFoot, m_scaledTileSize) + m_mapOffset, sf::Color::Green)
    };

    window.draw(line, 2, sf::Lines);
}

void Player::UpdateSheet(bool isMoving, float deltaTime)
{
    // Set sheet to activeSheet
    SheetLoader& sheet = SheetManager::Get(activeSheetID);
    int framesPerRow = sheet.frames.size() / 4;

    int newOffset = 0;
    if (m_lastClicked == 0) newOffset = 0;
    else if (m_lastClicked == 1) newOffset = framesPerRow;
    else if (m_lastClicked == 3) newOffset = framesPerRow * 2;
    else if (m_lastClicked == 2) newOffset = framesPerRow * 3;

    // Loop through sheet on a timer
    if (newOffset != m_sheetOffset || isMoving != m_wasMoving)
    {
        m_sheetOffset = newOffset;
        sheetIdx = 0;
        textureTimer = 0;
        m_sprite.setTextureRect(sheet.frames[m_sheetOffset].rect);
    }

    textureTimer += deltaTime;
    if (textureTimer > sheetRate)
    {
        textureTimer = 0;
        sheetIdx = (sheetIdx + 1) % framesPerRow;
        m_sprite.setTextureRect(sheet.frames[m_sheetOffset + sheetIdx].rect);
    }

    m_wasMoving = isMoving;
}
