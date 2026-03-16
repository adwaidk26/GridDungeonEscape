#include "GameTile.hpp"

#include "GameConstants.hpp"

CellTile::CellTile(int xPos, int yPos)
    : gridX(xPos),
      gridY(yPos),
      position{
          static_cast<float>(xPos * GameConstants::TILE_SIZE + GameConstants::TILE_SIZE / 2),
          static_cast<float>(yPos * GameConstants::TILE_SIZE + GameConstants::TILE_SIZE / 2)
      },
      isClimbable(false),
      isDestructible(false)
{
}

bool CellTile::getIsTileClimbable() const
{
    return isClimbable;
}

bool CellTile::getIsTileDestructible() const
{
    return isDestructible;
}

void CellTile::setTileClimbable(bool isClimbableValue)
{
    isClimbable = isClimbableValue;
}

void CellTile::setTileDestructible(bool isDestructibleValue)
{
    isDestructible = isDestructibleValue;
}

Vector2 CellTile::getTilePosition() const
{
    return position;
}
