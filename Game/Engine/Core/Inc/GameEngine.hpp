#pragma once

#include "AppState.hpp"

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
};
