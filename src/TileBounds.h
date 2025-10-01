#pragma once

#include <SFML/Graphics.hpp>

class TileBounds
{
    public:
        bool m_debugColorsEnabled;
        sf::Vector2f m_origin;

    private:
        sf::ConvexShape m_top;
        sf::ConvexShape m_bottom;
        sf::ConvexShape m_left;
        sf::ConvexShape m_right;
        sf::ConvexShape m_backL;
        sf::ConvexShape m_backR;

    public:
        TileBounds();
        ~TileBounds();

        void BuildBottom(const sf::Vector2f& pos, const sf::Vector2f& size);
        void BuildTop(const sf::Vector2f& pos, const sf::Vector2f& size, float height);
        void BuildWallLeft(const sf::Vector2f& pos, const sf::Vector2f& size, float height);
        void BuildWallRight(const sf::Vector2f& pos, const sf::Vector2f& size, float height);
        void BuildWallBackL(const sf::Vector2f& pos, const sf::Vector2f& size, float height);
        void BuildWallBackR(const sf::Vector2f& pos, const sf::Vector2f& size, float height);

        void SetOrigin(const sf::Vector2f& origin);

        std::vector<sf::Vector2f> GetVertices() const;

        const sf::ConvexShape& GetTop() const { return m_top; }
        const sf::ConvexShape& GetBottom() const { return m_bottom; }
        const sf::ConvexShape& GetWallLeft() const { return m_left; }
        const sf::ConvexShape& GetWallRight() const { return m_right; }
        const sf::ConvexShape& GetWallBackL() const { return m_backL; }
        const sf::ConvexShape& GetWallBackR() const { return m_backR; }
};
