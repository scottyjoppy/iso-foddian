#pragma once
#include "SheetLoader.h"
#include <map>

enum class SheetID
{
    PlayerIdle,
    PlayerWalk,
    TileSheet
};

class SheetManager
{
    private:
        static std::map<SheetID, SheetLoader> sheets;

    public:
        static void Load();
        static SheetLoader& Get(SheetID id);
};
