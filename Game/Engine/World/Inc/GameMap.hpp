#pragma once

#include <memory>
#include <string>
#include <vector>

#include "GameEntity.hpp"
#include "GameTile.hpp"

struct GameMapCell
{
    std::unique_ptr<GameEntity> entity;
    std::unique_ptr<CellTile> tile;
};

class GameMap
{
public:
    GameMap() = default;
    GameMap(int width, int height);

    bool LoadFromFiles(const std::string& entitiesFilePath, const std::string& tilesFilePath);

    void Resize(int width, int height);

    int GetWidth() const;
    int GetHeight() const;

    bool InBounds(int x, int y) const;

    const GameMapCell& GetCell(int x, int y) const;
    GameMapCell& GetCell(int x, int y);

    void SetEntity(int x, int y, std::unique_ptr<GameEntity> entity);

private:
    int width = 0;
    int height = 0;
    std::vector<std::vector<GameMapCell>> grid;
};
