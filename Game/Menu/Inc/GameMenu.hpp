#pragma once
#include "AppState.hpp"
#include <raylib.h>
#include "raygui.h"

class MenuState : public AppState
{
public:
    MenuState();
    ~MenuState();

    // Delete copy constructor and assignment operator to prevent double-free of Texture2D
    MenuState(const MenuState&) = delete;
    MenuState& operator=(const MenuState&) = delete;

    void Draw() override;
    void HandleInput() override;
    void Update() override;

private:
    Rectangle buttonStartGame;
    Rectangle buttonMapEditor;
    Rectangle buttonExit;
    Texture2D backgroundImage;

    int selectedButton; // -1: none, 0: Start Game, 1: Map Editor, 2: Exit
};