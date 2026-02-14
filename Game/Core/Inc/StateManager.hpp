#pragma once
#include "AppState.hpp"
#include <memory>

class StateManager
{
    public:
    static StateManager* GetInstance();

    void RequesetStateChange(AppStateID newState);
    void ProcessStateChange();

    private:
        StateManager() = default;
        ~StateManager() = default;
        StateManager(const StateManager&) = delete;
        StateManager& operator=(const StateManager&) = delete;
        
        std::unique_ptr<AppState> currentAppState = nullptr;
        AppStateID currentAppStateID = STATE_NONE;
        AppStateID pendingAppStateID = STATE_NONE;
};