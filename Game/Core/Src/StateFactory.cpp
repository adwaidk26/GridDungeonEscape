#include "StateFactory.hpp"
#include "Logger.hpp"
#include "GameMenu.hpp"
#include "GameEngine.hpp"
#include <memory>

std::unique_ptr<AppState> StateFactory::CreateState(AppStateID stateID) {
    switch (stateID) {
        case MENU:
            LOG_INFO("Creating MenuState");
            return std::make_unique<MenuState>();
        case GAME:
            LOG_INFO("Creating GameEngine state");
            return std::make_unique<GameEngine>();
        case MAP_EDITOR:
            LOG_WARN("MAP_EDITOR state not implemented");
            return nullptr;
        default:
            LOG_ERR("Unknown state ID");
            return nullptr;
    }
}
