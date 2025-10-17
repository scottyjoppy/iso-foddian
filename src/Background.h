#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Background
{
    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        std::vector<sf::IntRect> m_frames;
        int m_currentFrame;
        float m_timer;
        float m_frameRate;
        sf::Vector2f m_scale;

    public:
        Background();
        ~Background();

        bool Load(const std::string& filename, int frames, const sf::Vector2i& frameSize);
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);
};
