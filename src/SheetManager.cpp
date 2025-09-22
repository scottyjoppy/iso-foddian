#include "SheetManager.h"
#include <iostream>

std::map<SheetID, SheetLoader> SheetManager::sheets;

void SheetManager::Load()
{
    sheets.emplace(SheetID::PlayerIdle, SheetLoader("assets/textures/player/idle.png", {80, 80}, {16, 16}));
    sheets.emplace(SheetID::PlayerWalk, SheetLoader("assets/textures/player/walk.png", {80, 80}, {16, 16}));
    sheets.emplace(SheetID::Top, SheetLoader("assets/textures/tiles/tiletop.png", {16, 8}, {16, 8}, {0.f, 8.f}));
    sheets.emplace(SheetID::Left, SheetLoader("assets/textures/tiles/tileleft.png", {8, 12}, {8, 12}, {0.f, 4.f}));
    sheets.emplace(SheetID::Right, SheetLoader("assets/textures/tiles/tileright.png", {8, 12}, {8, 12}, {-8.f, 4.f}));

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
