#define RAYGUI_IMPLEMENTATION
#include "GameMenu.hpp"
#include "GameConstants.hpp"
#include "Logger.hpp"

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
    // Calculate scale based on design resolution (16:9 aspect ratio from GameConstants)
    float scaleX = (float)GetScreenWidth() / GameConstants::screenWidth;
    float scaleY = (float)GetScreenHeight() / GameConstants::screenHeight;
    float scale = (scaleX < scaleY) ? scaleX : scaleY;

    float destWidth = GameConstants::screenWidth * scale;
    float destHeight = GameConstants::screenHeight * scale;

    // Calculate offset to center the 16:9 content in the window
    float offsetX = (GetScreenWidth() - destWidth) * 0.5f;
    float offsetY = (GetScreenHeight() - destHeight) * 0.5f;

    if (backgroundImage.id != 0) {
        Rectangle src = {0.0f, 0.0f, (float)backgroundImage.width, (float)backgroundImage.height};
        Rectangle dst = {offsetX, offsetY, destWidth, destHeight};
        DrawTexturePro(backgroundImage, src, dst, {0.0f, 0.0f}, 0.0f, WHITE);
    }

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
