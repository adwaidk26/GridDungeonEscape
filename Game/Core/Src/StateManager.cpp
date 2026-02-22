#include "StateManager.hpp"
#include "StateFactory.hpp"
#include "Logger.hpp"

StateManager* StateManager::GetInstance()
{
    static StateManager instance;
    return &instance;
}

void StateManager::RequestStateChange(AppStateID appID)
{
    LOG_INFO("State change requested: %d", appID);
    pendingAppStateID = appID;
}

void StateManager::RequestQuit()
{
    LOG_INFO("Quit requested");
    quitRequested = true;
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

AppStateID StateManager::GetCurrentStateID() const
{
    return currentAppStateID;
}

bool StateManager::IsQuitRequested() const
{
    return quitRequested;
}

void StateManager::Update()
{
    if (currentAppState)
    {
        currentAppState->Update();
    }
}

void StateManager::Draw()
{
    if (currentAppState)
    {
        currentAppState->Draw();
    }
}

void StateManager::HandleInput()
{
    if (currentAppState)
    {
        currentAppState->HandleInput();
    }
}

void StateManager::Shutdown()
{
    pendingAppStateID = STATE_NONE;
    currentAppStateID = STATE_NONE;
    quitRequested = false;
    currentAppState.reset();
}
