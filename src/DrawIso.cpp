#include <iostream>
#include "DrawIso.h"

void DrawIso::DrawAll(std::vector<CubeTile*>& tiles, Player& p, sf::RenderWindow& window)
{
    std::vector<Drawable> drawList;
    drawList.reserve(tiles.size() + 1);

    for (auto* t : tiles)
    {
        if (!t->m_tileId)
            continue;

        Drawable tEntry;
        tEntry.sprite = &t->m_sprite;
        tEntry.depth = sf::Vector3f
            (
             t->m_gridCoords.x,
             t->m_gridCoords.y + 1,
             t->m_gridCoords.z
            );
        drawList.push_back(tEntry);
    }

    Drawable pEntry;
    pEntry.sprite = &p.m_sprite;
    pEntry.depth = sf::Vector3f
        (
         p.m_gridPos.x,
         p.m_gridPos.y,
         p.m_gridPos.z
        );
    drawList.push_back(pEntry);

    std::sort(drawList.begin(), drawList.end(),
            [](const Drawable& a, const Drawable& b)
            {
            float depthA = a.depth.x + a.depth.z - a.depth.y;
            float depthB = b.depth.x + b.depth.z - b.depth.y;
            return depthA < depthB;
            });

    for (auto& d : drawList)
    {
        window.draw(*d.sprite);
    }
}
