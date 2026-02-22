#pragma once

#include <cstdint>

enum class EntityType : uint8_t
{
    None = 0,
    Player = 1,
    Boulder = 2,
    Grass = 3,
    StoneWall = 4,
    Gem = 5
};
