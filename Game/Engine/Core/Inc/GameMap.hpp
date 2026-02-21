#pragma once

#include <string>
#include <vector>

#include "CellType.hpp"

struct GameMapCell
{
    TileType tile = TileType::Empty;
    EntityType entity = EntityType::None;
};

class GameMap
{
public:
    GameMap() = default;
    GameMap(int width, int height);

    bool LoadFromFile(const std::string& filePath);

    void Resize(int width, int height);

    int GetWidth() const;
    int GetHeight() const;

    bool InBounds(int x, int y) const;

    const GameMapCell& GetCell(int x, int y) const;
    GameMapCell& GetCell(int x, int y);

    void SetTile(int x, int y, TileType tile);
    void SetEntity(int x, int y, EntityType entity);

private:
    int width = 0;
    int height = 0;
    std::vector<std::vector<GameMapCell>> grid;
};
