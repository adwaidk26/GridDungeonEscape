#include "GameMap.hpp"

#include <cassert>

GameMap::GameMap(int widthIn, int heightIn)
{
    Resize(widthIn, heightIn);
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
