#define RAYGUI_IMPLEMENTATION
#include "GameMenu.hpp"
#include "GameConstants.hpp"
#include "Logger.hpp"
#include "LayoutUtils.hpp"
#include "StateManager.hpp"

MenuState::MenuState() : selectedButton(-1)
{
    LOG_INFO("MenuState created");
    int buttonWidth = 200;
    int buttonHeight = 60;
    int centerX = (GameConstants::screenWidth - buttonWidth) / 2 ;
    int startY = 300;
    int spacing = 100;

    buttonStartGame = {(float)centerX, (float)startY, (float)buttonWidth, (float)buttonHeight};
    buttonMapEditor = {(float)centerX, (float)(startY + spacing), (float)buttonWidth, (float)buttonHeight};
    buttonExit = {(float)centerX, (float)(startY + spacing * 2), (float)buttonWidth, (float)buttonHeight};
    
    backgroundImage = LoadTexture(TextFormat("%s/MenuImage.png", IMAGE_FOLDER));
    if (backgroundImage.id == 0) {
        LOG_WARN("Failed to load menu background image from %s/MenuImage.png", IMAGE_FOLDER);
    }

    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x3498DBFF);     // Blue button background
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xFFFFFFFF);     // White text
}

MenuState::~MenuState()
{
    if (backgroundImage.id != 0) {
        UnloadTexture(backgroundImage);
    }
}

void MenuState::Draw()
{
    // Get layout metrics from utility class
    const LayoutMetrics& layout = LayoutUtils::GetInstance().GetLayoutMetrics();

    if (backgroundImage.id != 0) {
        Rectangle src = {0.0f, 0.0f, (float)backgroundImage.width, (float)backgroundImage.height};
        Rectangle bgRect = {0.0f, 0.0f, (float)GameConstants::screenWidth, (float)GameConstants::screenHeight};
        DrawTexturePro(backgroundImage, src, LayoutUtils::GetInstance().ScaleRect(bgRect), {0.0f, 0.0f}, 0.0f, WHITE);
    }

    // Scale text size relative to the screen scale
    GuiSetStyle(DEFAULT, TEXT_SIZE, (int)(20 * layout.scale));

    if (GuiButton(LayoutUtils::GetInstance().ScaleRect(buttonStartGame), "Start Game")) {
        LOG_INFO("Start Game button clicked");
        selectedButton = 0;
    }
    if (GuiButton(LayoutUtils::GetInstance().ScaleRect(buttonMapEditor), "Map Editor")) {
        LOG_INFO("Map Editor button clicked");
        selectedButton = 1;
    }
    if (GuiButton(LayoutUtils::GetInstance().ScaleRect(buttonExit), "Exit")) {
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
            StateManager::GetInstance()->RequestStateChange(GAME);
            selectedButton = -1;
            break;
        case 1:
            LOG_INFO("Transitioning to MAP_EDITOR state");
            StateManager::GetInstance()->RequestStateChange(MAP_EDITOR);
            selectedButton = -1;
            break;
        case 2:
            LOG_INFO("Exit requested");
            StateManager::GetInstance()->RequestQuit();
            selectedButton = -1;
            break;
        default:
            break;
    }
}
