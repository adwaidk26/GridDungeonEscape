#include <raylib.h>
#include "Logger.hpp"
#include "GameConstants.hpp"
#include "StateManager.hpp"
#include "LayoutUtils.hpp"


int main()
{
    LOG_INFO("=== GridDungeonEscape Started ===");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(GameConstants::screenWidth, GameConstants::screenHeight, "GridDungeonEscape - Base");
    SetTargetFPS(GameConstants::targetFPS);

    StateManager* stateManager = StateManager::GetInstance();
    stateManager->RequestStateChange(MENU);

    while (!WindowShouldClose())
    {
        LayoutUtils::GetInstance().UpdateLayout();
        if (IsKeyPressed(KEY_F11))
        {
            ToggleFullscreen();
        }
        
        stateManager->ProcessStateChange();
        stateManager->HandleInput();
        stateManager->Update();
        
        BeginDrawing();
        ClearBackground({40, 40, 40, 255});
        stateManager->Draw();
        EndDrawing();
    }
    
    LOG_INFO("=== GridDungeonEscape Closed ===");
    stateManager->Shutdown();
    CloseWindow();
    return 0;
}
