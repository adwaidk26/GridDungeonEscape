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
    GameEntity* FindInitialControlledEntity() const;
    bool MoveEntity(int fromX, int fromY, int toX, int toY);
    bool TryMoveEntity(int fromX, int fromY, int dx, int dy, int power);

    static constexpr int PLAYER_PUSH_POWER = 1;
    GameEntity* movementControlledEntity = nullptr;
    int tickCounter = 0;
    GameMap gameMap;
    GameRenderer gameRenderer;
};
