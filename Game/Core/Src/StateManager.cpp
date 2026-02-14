#include "StateManager.hpp"
#include "StateFactory.hpp"

StateManager* StateManager::GetInstance()
{
    static StateManager instance;
    return &instance;
}

void StateManager::RequesetStateChange(AppStateID appID)
{
    pendingAppStateID = appID;
}

void StateManager::ProcessStateChange()
{
    if(pendingAppStateID == STATE_NONE)
    {
        return;
    }
    currentAppState = StateFactory::CreateState(pendingAppStateID);
    currentAppStateID = pendingAppStateID;
    pendingAppStateID = STATE_NONE;
}