#include "GameRenderer.hpp"

GameRenderer::GameRenderer(const GameMap& gameMapRef) : gameMap(gameMapRef) {}

void GameRenderer::Draw() const
{
    for (int y = 0; y < gameMap.GetHeight(); ++y) {
        for (int x = 0; x < gameMap.GetWidth(); ++x) {
            const GameMapCell& cell = gameMap.GetCell(x, y);
            if (cell.entity) {
                cell.entity->Draw();
            }
        }
    }
}
