#include "SheetManager.h"
#include <iostream>

std::map<SheetID, SheetLoader> SheetManager::sheets;

void SheetManager::Load()
{
    sheets.emplace(SheetID::PlayerIdle, SheetLoader("assets/textures/player/idle.png", {80, 80}, {16, 16}));
    sheets.emplace(SheetID::PlayerWalk, SheetLoader("assets/textures/player/walk.png", {80, 80}, {16, 16}));
    sheets.emplace(SheetID::TileSheet, SheetLoader("assets/textures/tiles/tilesheet.png", {16, 16}, {16, 16}, {0.f, 8.f}));

    for (auto& [id, sheet] : sheets)
    {
        std::cout << "Loading " << sheet.m_fileDir << std::endl;
        sheet.Load();
    }
}

SheetLoader& SheetManager::Get(SheetID id)
{
    return sheets.at(id);
}
