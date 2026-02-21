#include "GameMap.hpp"

#include <cassert>
#include <fstream>
#include <string>
#include <vector>

#include "Logger.hpp"

namespace {

bool ParseMapSymbol(char symbol, GameMapCell& outCell)
{
    outCell = {};

    switch (symbol) {
        case '.':
        case ' ':
            outCell.tile = TileType::Empty;
            outCell.entity = EntityType::None;
            return true;
        case '#':
            outCell.tile = TileType::Wall;
            outCell.entity = EntityType::None;
            return true;
        case 'D':
            outCell.tile = TileType::Dirt;
            outCell.entity = EntityType::None;
            return true;
        case 'P':
            outCell.tile = TileType::Empty;
            outCell.entity = EntityType::Player;
            return true;
        case 'B':
            outCell.tile = TileType::Empty;
            outCell.entity = EntityType::Boulder;
            return true;
        case 'G':
            outCell.tile = TileType::Empty;
            outCell.entity = EntityType::Gem;
            return true;
        case 'S':
            outCell.tile = TileType::Wall;
            outCell.entity = EntityType::StoneWall;
            return true;
        case 'R':
            outCell.tile = TileType::Dirt;
            outCell.entity = EntityType::Grass;
            return true;
        default:
            return false;
    }
}

}  // namespace

GameMap::GameMap(int widthIn, int heightIn)
{
    Resize(widthIn, heightIn);
}

bool GameMap::LoadFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        LOG_ERR("Failed to open map file: %s", filePath.c_str());
        return false;
    }

    std::vector<std::string> rows;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            continue;
        }
        rows.push_back(line);
    }

    if (rows.empty()) {
        LOG_ERR("Map file is empty: %s", filePath.c_str());
        return false;
    }

    const size_t expectedWidth = rows.front().size();
    if (expectedWidth == 0) {
        LOG_ERR("Map has zero-width rows: %s", filePath.c_str());
        return false;
    }

    for (size_t y = 0; y < rows.size(); ++y) {
        if (rows[y].size() != expectedWidth) {
            LOG_ERR(
                "Map row width mismatch at row %zu in %s (expected %zu, got %zu)",
                y,
                filePath.c_str(),
                expectedWidth,
                rows[y].size()
            );
            return false;
        }
    }

    Resize(static_cast<int>(expectedWidth), static_cast<int>(rows.size()));

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
            grid[y][x] = parsedCell;
        }
    }

    LOG_INFO("Loaded map: %s (%dx%d)", filePath.c_str(), width, height);
    return true;
}

void GameMap::Resize(int widthIn, int heightIn)
{
    width = (widthIn < 0) ? 0 : widthIn;
    height = (heightIn < 0) ? 0 : heightIn;
    grid.assign(height, std::vector<GameMapCell>(width));
}

int GameMap::GetWidth() const
{
    return width;
}

int GameMap::GetHeight() const
{
    return height;
}

bool GameMap::InBounds(int x, int y) const
{
    return x >= 0 && y >= 0 && x < width && y < height;
}

const GameMapCell& GameMap::GetCell(int x, int y) const
{
    assert(InBounds(x, y));
    return grid[y][x];
}

GameMapCell& GameMap::GetCell(int x, int y)
{
    assert(InBounds(x, y));
    return grid[y][x];
}

void GameMap::SetTile(int x, int y, TileType tile)
{
    if (!InBounds(x, y)) {
        return;
    }
    grid[y][x].tile = tile;
}

void GameMap::SetEntity(int x, int y, EntityType entity)
{
    if (!InBounds(x, y)) {
        return;
    }
    grid[y][x].entity = entity;
}
