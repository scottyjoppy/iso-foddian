#pragma once
#include <iostream>
#include <string>
#include <vector>

struct MapData
{
    int mapW = 0;
    int mapH = 0;
    std::vector<int> tileIds;
};


class MapLoader
{
    public:
        bool Load(const std::string& filename, MapData& mapData);
        bool Save(const std::string& filename, const MapData& mapData);
};
