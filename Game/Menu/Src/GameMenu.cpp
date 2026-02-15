#define RAYGUI_IMPLEMENTATION
#include "GameMenu.hpp"
#include "GameConstants.hpp"
#include "Logger.hpp"

MenuState::MenuState() : selectedButton(-1)
{
    LOG_INFO("MenuState created");
    int buttonWidth = 200;
    int buttonHeight = 60;
    int centerX = (GameConstants::screenWidth - buttonWidth) / 2;
    int startY = 200;
    int spacing = 100;

    buttonStartGame = {(float)centerX, (float)startY, (float)buttonWidth, (float)buttonHeight};
    buttonMapEditor = {(float)centerX, (float)(startY + spacing), (float)buttonWidth, (float)buttonHeight};
    buttonExit = {(float)centerX, (float)(startY + spacing * 2), (float)buttonWidth, (float)buttonHeight};
    
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x3498DBFF);     // Blue button background
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xFFFFFFFF);     // White text
}

MenuState::~MenuState()
{
}

void MenuState::Draw()
{
    int titleSize = 40;
    const char* title = "Grid Dungeon Escape";
    int titleWidth = MeasureText(title, titleSize);
    int titleX = (GameConstants::screenWidth - titleWidth) / 2;
    DrawText(title, titleX, 80, titleSize, DARKBLUE);

    if (GuiButton(buttonStartGame, "Start Game")) {
        LOG_INFO("Start Game button clicked");
        selectedButton = 0;
    }
    if (GuiButton(buttonMapEditor, "Map Editor")) {
        LOG_INFO("Map Editor button clicked");
        selectedButton = 1;
    }
    if (GuiButton(buttonExit, "Exit")) {
        LOG_INFO("Exit button clicked");
        selectedButton = 2;
    }
}

void MenuState::HandleInput()
{
    if (IsKeyPressed(KEY_ESCAPE)) {
        LOG_INFO("ESC key pressed - Exit requested");
        selectedButton = 2;
    }
}

void MenuState::Update()
{
    switch (selectedButton) {
        case 0:
            LOG_INFO("Transitioning to GAME state");
            selectedButton = -1;
            break;
        case 1:
            LOG_INFO("Transitioning to MAP_EDITOR state");
            selectedButton = -1;
            break;
        case 2:
            LOG_INFO("Exit requested");
            selectedButton = -1;
            break;
        default:
            break;
    }
}