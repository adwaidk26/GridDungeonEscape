#pragma once

#include "GameMap.hpp"

namespace GameMapParser {

bool LoadMapFromFiles(
    const std::string& entitiesFilePath,
    const std::string& tilesFilePath,
    std::vector<std::vector<GameMapCell>>& outGrid,
    int& outWidth,
    int& outHeight
);

}  // namespace GameMapParser
