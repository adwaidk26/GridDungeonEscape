#include "GameEngine.hpp"
#include <raylib.h>

#include "GameConstants.hpp"
#include "LayoutUtils.hpp"
#include "Logger.hpp"
#include "StateManager.hpp"

GameEngine::GameEngine() : gameRenderer(gameMap)
{
    gameMap.LoadFromFile(TextFormat("%s/level1.map", MAP_FOLDER));
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
    }
}

void GameEngine::Update()
{
    tickCounter++;
    if (tickCounter == 1) {
        LOG_INFO("GameEngine state running");
    }
}
