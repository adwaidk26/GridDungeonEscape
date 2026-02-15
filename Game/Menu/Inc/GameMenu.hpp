#pragma once
#include "AppState.hpp"
#include <raylib.h>
#include "raygui.h"

class MenuState : public AppState
{
public:
    MenuState();
    ~MenuState();
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