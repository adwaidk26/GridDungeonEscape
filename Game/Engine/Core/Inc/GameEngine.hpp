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
    bool ShouldApplyGravityTo(const GameEntity& entity) const;
    void ApplyGravity();
    bool MoveEntity(int fromX, int fromY, int toX, int toY);
    bool TryMoveEntity(int fromX, int fromY, int dx, int dy, int power);

    static constexpr int PLAYER_PUSH_POWER = 1;
    static constexpr int GRAVITY_STEP_TICKS = 8;
    GameEntity* movementControlledEntity = nullptr;
    int tickCounter = 0;
    GameMap gameMap;
    GameRenderer gameRenderer;
};
