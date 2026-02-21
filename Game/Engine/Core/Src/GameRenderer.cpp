#include "GameRenderer.hpp"
#include <raylib.h>
#include "LayoutUtils.hpp"

GameRenderer::GameRenderer(const GameMap& gameMapRef) : gameMap(gameMapRef) {}

void GameRenderer::Draw() const
{
    (void)gameMap;
}
