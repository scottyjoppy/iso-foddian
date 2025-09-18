#include "SheetManager.h"

std::map<SheetID, SheetLoader> SheetManager::sheets;

void SheetManager::Load()
{
    sheets.emplace(SheetID::PlayerIdle, SheetLoader("assets/textures/player/idle.png", {80, 80}, {16, 16}));
    sheets.emplace(SheetID::PlayerWalk, SheetLoader("assets/textures/player/walk.png", {80, 80}, {16, 16}));
    sheets.emplace(SheetID::Floor, SheetLoader("assets/textures/tiles/tiletop.png", {16, 8}, {16, 8}));

    for (auto& [id, sheet] : sheets) sheet.Load();
}

SheetLoader& SheetManager::Get(SheetID id)
{
    return sheets.at(id);
}
