#include "GameMap.hpp"

#include <cassert>
#include <memory>
#include <vector>

#include "GameMapParser.hpp"

GameMap::GameMap(int widthIn, int heightIn)
{
    Resize(widthIn, heightIn);
}

bool GameMap::LoadFromFile(const std::string &filePath)
{
    int parsedWidth = 0;
    int parsedHeight = 0;
    std::vector<std::vector<GameMapCell>> parsedGrid;
    const bool loaded = GameMapParser::LoadMapFromFile(filePath, parsedGrid, parsedWidth, parsedHeight);
    if (!loaded)
    {
        return false;
    }
    width = parsedWidth;
    height = parsedHeight;
    grid = std::move(parsedGrid);
    return true;
}

void GameMap::Resize(int widthIn, int heightIn)
{
    width = (widthIn < 0) ? 0 : widthIn;
    height = (heightIn < 0) ? 0 : heightIn;
    grid.clear();
    grid.resize(height);
    for (auto& row : grid)
    {
        row.resize(width);
    }
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

const GameMapCell &GameMap::GetCell(int x, int y) const
{
    assert(InBounds(x, y));
    return grid[y][x];
}

GameMapCell &GameMap::GetCell(int x, int y)
{
    assert(InBounds(x, y));
    return grid[y][x];
}

void GameMap::SetEntity(int x, int y, std::unique_ptr<GameEntity> entity)
{
    if (!InBounds(x, y))
    {
        return;
    }
    grid[y][x].entity = std::move(entity);
}
