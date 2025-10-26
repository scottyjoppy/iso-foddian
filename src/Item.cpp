#include "Item.h"

#include "Math.h"
#include <iostream>

Item::Item(const sf::Vector2f& tileSize, sf::Vector3i gridPos, SheetID id, const sf::Vector2f& mapOffset, int logicalHeight) :
    m_tileSize(tileSize),
    m_gridPos(gridPos),
    m_mapOffset(mapOffset),
    m_scale(1.f),
    m_cubeHeight(0),
    m_logicalHeight(logicalHeight),
    m_id(id),
    sheetIdx(0),
    m_sheetRate(0.2f),
    m_sheetAcc(0.f),
    showShadow(true),
    debugging(false)
{
    SetTile(m_id);
    Initialize();
}

Item::~Item()
{
}

void Item::Initialize()
{
    m_scale = Math::CalcScale(m_tileSize);
    sf::Vector2f pos = Math::IsoTransform(sf::Vector3f(m_gridPos), m_tileSize * m_scale);

    m_mapPos = pos + m_mapOffset;
    m_sprite.setPosition(m_mapPos);
    m_sprite.setScale(m_scale * 2.f, m_scale * 2.f);

    m_cubeHeight = m_tileSize.y * m_scale;
    //std::cout << m_mapPos.x << " " << m_mapPos.y << std::endl;

    m_shadow.setRadius(m_tileSize.x * m_scale / 4);
    m_shadow.setFillColor(sf::Color(0, 0, 0, 128));
    m_shadow.setOrigin(m_shadow.getRadius(), -m_shadow.getRadius());
    m_shadow.setScale(1.f, 0.5f);

    m_shadow.setPosition(m_mapPos.x, m_mapPos.y);
 }

void Item::Update(float deltaTime)
{
    m_sheetAcc += deltaTime;

    if (m_sheetAcc >= m_sheetRate)
    {
        SheetLoader& sheet = SheetManager::Get(m_id);
        int frames = sheet.frames.size();
        sheetIdx = (sheetIdx + 1) % frames;
        m_sprite.setTextureRect(sheet.frames[sheetIdx].rect);
        m_sheetAcc = 0;
    }
}

void Item::Draw(sf::RenderWindow& window)
{
    if (showShadow)
        window.draw(m_shadow);
    window.draw(m_sprite);
}

void Item::SetTile(SheetID id)
{
    auto& sheet = SheetManager::Get(id);
    m_sprite.setTexture(sheet.m_texture);

    if (0 < sheet.frames.size())
        m_sprite.setTextureRect(sheet.frames[sheetIdx].rect);
    else
        std::cerr << "Warning: invalid id " << std::endl;
    m_sprite.setOrigin(sheet.m_origin);
}

std::unique_ptr<Item> Item::Create(const sf::Vector2f& tileSize, const sf::Vector2f& mapOffset)
{
    int randX = std::rand() % 10;
    int randZ = std::rand() % 10;

    return std::make_unique<Item>(tileSize, sf::Vector3i(randX, 1, randZ), SheetID::Item, mapOffset, 1);
}
