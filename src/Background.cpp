#include "Background.h"

Background::Background() :
    m_currentFrame(0), m_timer(0.f), m_frameRate(0.1f)
{
}

Background::~Background()
{
}

bool Background::Load(const std::string& filename, int frames, const sf::Vector2i& frameSize, float frameRate = 0.1f)
{
    if (!m_texture.loadFromFile(filename))
        return false;

    m_frameRate = frameRate;

    for (int i = 0; i < frames; i++)
    {
        sf::IntRect rect(i * frameSize.x, 0, frameSize.x, frameSize.y);
        m_frames.push_back(rect);
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(m_frames[0]);

    return true;
}

void Background::Update(float deltaTime)
{
    m_timer += deltaTime;
    if (m_timer >= m_frameRate)
    {
        m_timer = 0.f;
        m_currentFrame = (m_currentFrame + 1) % m_frames.size();
        m_sprite.setTextureRect(m_frames[m_currentFrame]);
    }
    m_sprite.setScale(4, 4);
}

void Background::Draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}
