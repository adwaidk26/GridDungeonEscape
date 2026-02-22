#pragma once

#include "GameMap.hpp"

namespace GameMapParser {

bool ParseMapSymbol(char symbol, GameMapCell& outCell);
bool LoadMapFromFile(const std::string& filePath, std::vector<std::vector<GameMapCell>>& outGrid, int& outWidth, int& outHeight);

}  // namespace GameMapParser
