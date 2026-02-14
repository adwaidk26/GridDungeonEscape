#pragma once
#include "AppState.hpp"
#include <memory>

class StateFactory
{
    public:
    static std::unique_ptr<AppState> CreateState(AppStateID stateID);
};