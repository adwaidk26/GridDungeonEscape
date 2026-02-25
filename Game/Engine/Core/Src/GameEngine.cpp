#include "GameEngine.hpp"
#include <raylib.h>

#include <utility>

#include "GameConstants.hpp"
#include "LayoutUtils.hpp"
#include "Logger.hpp"
#include "StateManager.hpp"

GameEngine::GameEngine() : gameRenderer(gameMap)
{
    const bool loaded = gameMap.LoadFromFile(TextFormat("%s/level1.map", MAP_FOLDER));
    if (!loaded) {
        LOG_ERR("Failed to load map for GameEngine");
    }

    movementControlledEntity = FindInitialControlledEntity();
    if (!movementControlledEntity) {
        LOG_WARN("No collector entity found for movement control");
    }

    LOG_INFO("GameEngine state created");
}

GameEngine::~GameEngine()
{
    LOG_INFO("GameEngine state destroyed");
}

void GameEngine::Draw()
{
    const LayoutMetrics& layout = LayoutUtils::GetInstance().GetLayoutMetrics();
    const char* message = "Game Engine State (placeholder)";
    int fontSize = (int)(28 * layout.scale);
    if (fontSize < 12) {
        fontSize = 12;
    }

    int textWidth = MeasureText(message, fontSize);
    int x = (int)(layout.offsetX + (layout.destWidth - textWidth) * 0.5f);
    int y = (int)(layout.offsetY + 40 * layout.scale);

    DrawText(message, x, y, fontSize, RAYWHITE);

    const char* hint = "Press ESC to return to menu";
    int hintSize = (int)(18 * layout.scale);
    if (hintSize < 10) {
        hintSize = 10;
    }
    int hintWidth = MeasureText(hint, hintSize);
    int hx = (int)(layout.offsetX + (layout.destWidth - hintWidth) * 0.5f);
    int hy = (int)(layout.offsetY + 80 * layout.scale);
    DrawText(hint, hx, hy, hintSize, LIGHTGRAY);
    gameRenderer.Draw();
}

void GameEngine::HandleInput()
{
    if (IsKeyPressed(KEY_ESCAPE)) {
        LOG_INFO("ESC pressed - returning to MENU");
        StateManager::GetInstance()->RequestStateChange(MENU);
        return;
    }

    int dx = 0;
    int dy = 0;
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
        dy = -1;
    } else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
        dy = 1;
    } else if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) {
        dx = -1;
    } else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
        dx = 1;
    }

    if (dx == 0 && dy == 0) {
        return;
    }

    if (!movementControlledEntity) {
        LOG_WARN("No movement-controlled entity assigned");
        return;
    }

    const int controlledX = movementControlledEntity->GetGridX();
    const int controlledY = movementControlledEntity->GetGridY();
    if (!gameMap.InBounds(controlledX, controlledY)) {
        LOG_WARN("Movement-controlled entity has out-of-bounds grid position (%d, %d)", controlledX, controlledY);
        return;
    }

    GameMapCell& controlledCell = gameMap.GetCell(controlledX, controlledY);
    if (controlledCell.entity.get() != movementControlledEntity) {
        LOG_WARN("Movement-controlled entity pointer is stale");
        return;
    }

    TryMoveEntity(controlledX, controlledY, dx, dy, PLAYER_PUSH_POWER);
}

void GameEngine::Update()
{
    tickCounter++;
    if (tickCounter == 1) {
        LOG_INFO("GameEngine state running");
    }

    if (tickCounter % GRAVITY_STEP_TICKS == 0) {
        ApplyGravity();
    }
}
//temporary function
GameEntity* GameEngine::FindInitialControlledEntity() const
{
    for (int y = 0; y < gameMap.GetHeight(); ++y) {
        for (int x = 0; x < gameMap.GetWidth(); ++x) {
            const GameMapCell& cell = gameMap.GetCell(x, y);
            if (!cell.entity) {
                continue;
            }
            if (!cell.entity->IsCollector()) {
                continue;
            }
            return cell.entity.get();
        }
    }
    return nullptr;
}

bool GameEngine::ShouldApplyGravityTo(const GameEntity& entity) const
{
    return entity.IsGravityApplicable();
}

void GameEngine::ApplyGravity()
{
    const int mapWidth = gameMap.GetWidth();
    const int mapHeight = gameMap.GetHeight();
    if (mapWidth <= 0 || mapHeight <= 1) {
        return;
    }

    for (int y = mapHeight - 2; y >= 0; --y) {
        for (int x = 0; x < mapWidth; ++x) {
            GameMapCell& sourceCell = gameMap.GetCell(x, y);
            if (!sourceCell.entity) {
                continue;
            }

            GameEntity* entity = sourceCell.entity.get();
            if (!ShouldApplyGravityTo(*entity)) {
                continue;
            }

            const int targetY = y + 1;
            if (gameMap.GetCell(x, targetY).entity) {
                continue;
            }

            MoveEntity(x, y, x, targetY);
        }
    }
}

bool GameEngine::MoveEntity(int fromX, int fromY, int toX, int toY)
{
    if (!gameMap.InBounds(fromX, fromY) || !gameMap.InBounds(toX, toY)) {
        return false;
    }

    GameMapCell& fromCell = gameMap.GetCell(fromX, fromY);
    GameMapCell& toCell = gameMap.GetCell(toX, toY);
    if (!fromCell.entity || toCell.entity) {
        return false;
    }

    toCell.entity = std::move(fromCell.entity);
    toCell.entity->SetGridPosition(toX, toY);
    toCell.entity->SetPosition(GameEntity::GetWorldPosFromGridPos(toX, toY));
    return true;
}

bool GameEngine::TryMoveEntity(int fromX, int fromY, int dx, int dy, int power)
{
    if (!gameMap.InBounds(fromX, fromY)) {
        return false;
    }

    const int targetX = fromX + dx;
    const int targetY = fromY + dy;
    if (!gameMap.InBounds(targetX, targetY)) {
        return false;
    }

    GameMapCell& fromCell = gameMap.GetCell(fromX, fromY);
    if (!fromCell.entity) {
        return false;
    }

    GameEntity* mover = fromCell.entity.get();
    GameMapCell& targetCell = gameMap.GetCell(targetX, targetY);
    if (!targetCell.entity) {
        return MoveEntity(fromX, fromY, targetX, targetY);
    }

    GameEntity* target = targetCell.entity.get();
    if (target->IsCollectable()) {
        if (!mover->IsCollector()) {
            return false;
        }
        targetCell.entity.reset();
        return MoveEntity(fromX, fromY, targetX, targetY);
    }

    if (!target->IsMovable() || power <= 0) {
        return false;
    }

    if (!TryMoveEntity(targetX, targetY, dx, dy, power - 1)) {
        return false;
    }

    return MoveEntity(fromX, fromY, targetX, targetY);
}
