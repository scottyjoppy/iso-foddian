#include <iostream>
#include "DrawIso.h"

void DrawIso::DrawAll(std::vector<CubeTile*>& tiles, Player& p, Item& i, sf::RenderWindow& window)
{
    std::vector<Drawable> drawList;
    drawList.reserve(tiles.size() + 2);

    for (auto* t : tiles)
    {
        if (!t->m_tileId) continue;

        Drawable tEntry;
        tEntry.type = DrawableType::CubeTile;
        tEntry.entity = t;
        tEntry.depth = sf::Vector3f
            (
             t->m_gridCoords.x - 1,
             t->m_gridCoords.y + 1,
             t->m_gridCoords.z
            );
        drawList.push_back(tEntry);
    }

    Drawable pEntry;
    pEntry.type = DrawableType::Player;
    pEntry.entity = &p;
    pEntry.depth = sf::Vector3f
        (
         p.m_gridPos.x,
         p.m_gridPos.y - 0.5f,
         p.m_gridPos.z
        );
    drawList.push_back(pEntry);

    Drawable iEntry;
    iEntry.type = DrawableType::Item;
    iEntry.entity = &i;
    iEntry.depth = sf::Vector3f
        (
         i.m_gridPos.x - 1.f,
         i.m_gridPos.y - 1.f,
         i.m_gridPos.z
        );
    drawList.push_back(iEntry);

    std::sort(drawList.begin(), drawList.end(),
            [](const Drawable& a, const Drawable& b)
            {
            float depthA = a.depth.x + a.depth.z - (a.depth.y);
            float depthB = b.depth.x + b.depth.z - (b.depth.y);
            return depthA < depthB;
            });

    for (auto& d : drawList)
    {
        d.Draw(window);
    }
}
