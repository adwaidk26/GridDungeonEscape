#include <raylib.h>
#include "Logger.hpp"
#include "GameConstants.hpp"


int main()
{
    InitWindow(GameConstants::screenWidth, GameConstants::screenHeight, "GridDungeonEscape - Base");
    SetTargetFPS(GameConstants::targetFPS);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F11))
        {
            ToggleFullscreen();
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("GridDungeonEscape - Base", 200, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}