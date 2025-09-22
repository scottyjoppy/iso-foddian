#include "MapLoader.h"

#include <fstream>
#include <sstream>
#include <algorithm>

bool MapLoader::Load(const std::string& filename, MapData& mapData)
{
	std::ifstream file(filename);
	if (!file.is_open())
    {
        std::cerr << "Unable to open " << filename << std::endl;
        return false;
    }

    std::string line;
    bool isMapValid = false;

    while (std::getline(file, line))
    {
        if (!isMapValid)
        {
            if (line == "[Map]")
            {
                isMapValid = true;
                continue;
            }
            else
            {
                std::cerr << "Map file " << filename << " is not valie!" << std::endl;
                return false;
            }
        }

        try
        {
            auto eqPos = line.find("=");
            if (eqPos == std::string::npos) continue;

            std::string key = line.substr(0, eqPos);
            std::string value = line.substr(eqPos + 1);

            if (key == "width") mapData.mapW = std::stoi(value);
            else if (key == "height") mapData.mapH = std::stoi(value);
            else if (key == "data")
            {
                std::stringstream ss(value);
                std::string token;
                mapData.tileIds.clear();

                while (std::getline(ss, token, ','))
                {
                    mapData.tileIds.push_back(std::stoi(token));
                }
            }

            if (mapData.tileIds.size() != mapData.mapW * mapData.mapH)
            {
                std::cerr << "ERROR: Map data length (" 
                          << mapData.tileIds.size() 
                          << ") does not match mapWidth*mapHeight (" 
                          << mapData.mapW * mapData.mapH << ")!" 
                          << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error parsing map file " << filename << ": " << e.what() << std::endl;
            return false;
        }
    }
    file.close();
    return true;
}

//bool MapLoader::Save(const std::string& filenamem const MapData& mapData)
//{
//    // TODO Implement Save
//    return false;
//}
