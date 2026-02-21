#pragma once

#include "GameMap.hpp"

class GameRenderer
{
public:
    explicit GameRenderer(const GameMap& gameMapRef);

    void Draw() const;

private:
    const GameMap& gameMap;
};
