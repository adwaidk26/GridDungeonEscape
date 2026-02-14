#pragma once

enum AppStateID
{
    STATE_NONE,
    MENU,
    GAME,
    MAP_EDITOR,
};

/**
 * @brief Abstract base class for all application states
 * 
 * Defines the interface that all states must implement for the state machine.
 * Uses the State design pattern to manage different game/app modes.
 */
class AppState
{
    public:
    AppState();
    virtual ~AppState() {};
    virtual void Draw() = 0;
    virtual void HandleInput() = 0;
    virtual void Update() = 0;
};