#include "StateFactory.hpp"
#include "Logger.hpp"

std::unique_ptr<AppState> StateFactory::CreateState(AppStateID stateID) {
    LOG_INFO("Creating State");
    switch (stateID) {
        default:
            return nullptr;
    }
}
