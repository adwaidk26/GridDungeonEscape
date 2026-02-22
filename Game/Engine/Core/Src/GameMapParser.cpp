#include "GameMapParser.hpp"

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "DefaultGameEntities.hpp"
#include "Logger.hpp"

namespace GameMapParser {

namespace {

bool ReadRowsFromFile(const std::string& filePath, std::vector<std::string>& outRows)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        LOG_ERR("Failed to open map file: %s", filePath.c_str());
        return false;
    }

    outRows.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            continue;
        }
        outRows.push_back(line);
    }

    if (outRows.empty()) {
        LOG_ERR("Map file is empty: %s", filePath.c_str());
        return false;
    }

    return true;
}

bool ValidateRows(const std::vector<std::string>& rows, const std::string& filePath, size_t& outExpectedWidth)
{
    outExpectedWidth = rows.front().size();
    if (outExpectedWidth == 0) {
        LOG_ERR("Map has zero-width rows: %s", filePath.c_str());
        return false;
    }

    for (size_t y = 0; y < rows.size(); ++y) {
        if (rows[y].size() != outExpectedWidth) {
            LOG_ERR(
                "Map row width mismatch at row %zu in %s (expected %zu, got %zu)",
                y,
                filePath.c_str(),
                outExpectedWidth,
                rows[y].size()
            );
            return false;
        }
    }

    return true;
}

void ResizeOutputGrid(int width, int height, std::vector<std::vector<GameMapCell>>& outGrid)
{
    outGrid.clear();
    outGrid.resize(static_cast<size_t>(height));
    for (auto& row : outGrid) {
        row.resize(static_cast<size_t>(width));
    }
}

bool ParseRowsIntoGrid(const std::vector<std::string>& rows, const std::string& filePath, std::vector<std::vector<GameMapCell>>& outGrid)
{
    for (size_t y = 0; y < rows.size(); ++y) {
        for (size_t x = 0; x < rows[y].size(); ++x) {
            GameMapCell parsedCell{};
            if (!ParseMapSymbol(rows[y][x], parsedCell)) {
                LOG_ERR(
                    "Unknown map symbol '%c' at (%zu, %zu) in %s",
                    rows[y][x],
                    x,
                    y,
                    filePath.c_str()
                );
                return false;
            }
            if (parsedCell.entity) 
            {
                parsedCell.entity->SetPosition(
                    GameEntity::GetWorldPosFromGridPos(static_cast<int>(x), static_cast<int>(y))
                );
                parsedCell.entity->SetGridPosition(static_cast<int>(x), static_cast<int>(y));
            }
            outGrid[y][x] = std::move(parsedCell);
        }
    }

    return true;
}

}  // namespace

bool ParseMapSymbol(char symbol, GameMapCell& outCell)
{
    outCell = {};

    switch (symbol) {
        case '.':
        case ' ':
            return true;
        case '#':
            return true;
        case 'D':
            return true;
        case 'P':
            outCell.entity = std::make_unique<PlayerEntity>();
            return true;
        case 'B':
            outCell.entity = std::make_unique<BoulderEntity>();
            return true;
        case 'G':
            outCell.entity = std::make_unique<GemEntity>();
            return true;
        case 'S':
            outCell.entity = std::make_unique<StoneWallEntity>();
            return true;
        case 'R':
            outCell.entity = std::make_unique<GrassEntity>();
            return true;
        default:
            return false;
    }
}

bool LoadMapFromFile(const std::string& filePath, std::vector<std::vector<GameMapCell>>& outGrid, int& outWidth, int& outHeight)
{
    std::vector<std::string> rows;
    if (!ReadRowsFromFile(filePath, rows)) {
        return false;
    }

    size_t expectedWidth = 0;
    if (!ValidateRows(rows, filePath, expectedWidth)) {
        return false;
    }

    outWidth = static_cast<int>(expectedWidth);
    outHeight = static_cast<int>(rows.size());
    ResizeOutputGrid(outWidth, outHeight, outGrid);

    if (!ParseRowsIntoGrid(rows, filePath, outGrid)) {
        return false;
    }

    LOG_INFO("Loaded map: %s (%dx%d)", filePath.c_str(), outWidth, outHeight);
    return true;
}

}  // namespace GameMapParser
