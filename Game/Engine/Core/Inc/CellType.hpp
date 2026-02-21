#pragma once

#include <cstdint>

enum class TileType : uint8_t
{
    Empty = 0,
    Dirt = 1,
    Wall = 2
};

enum class EntityType : uint8_t
{
    None = 0,
    Player = 1,
    Boulder = 2,
    Grass = 3,
    StoneWall = 4,
    Gem = 5
};
