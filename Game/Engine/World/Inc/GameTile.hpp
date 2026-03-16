#pragma once

#include <raylib.h>

class CellTile
{
public:
    CellTile(int xPos, int yPos);
    virtual ~CellTile() = default;
    bool getIsTileClimbable() const;
    bool getIsTileDestructible() const;
    void setTileClimbable();
    void setTileDestructible();
    virtual void drawTile() = 0;

protected:
    Vector2 getTilePosition() const;

private:
    int gridX;
    int gridY;
    Vector2 position;
    bool isClimbable;
    bool isDestructible;
};
