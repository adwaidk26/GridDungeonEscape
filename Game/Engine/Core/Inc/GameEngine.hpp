#pragma once

#include "AppState.hpp"
#include "GameMap.hpp"
#include "GameRenderer.hpp"

class GameEngine : public AppState
{
public:
    GameEngine();
    ~GameEngine() override;

    void Draw() override;
    void HandleInput() override;
    void Update() override;

private:
    int tickCounter = 0;
    GameMap gameMap;
    GameRenderer gameRenderer;
};
