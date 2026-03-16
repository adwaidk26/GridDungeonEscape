#pragma once

#include "GameTile.hpp"

class MetalGrillTile final : public CellTile
{
public:
    MetalGrillTile(int xPos, int yPos);
    void drawTile() override;
};

class MetalWallTile final : public CellTile
{
public:
    MetalWallTile(int xPos, int yPos);
    void drawTile() override;
};

class MudWallTile final : public CellTile
{
public:
    MudWallTile(int xPos, int yPos);
    void drawTile() override;
};

class VinesWallTile final : public CellTile
{
public:
    VinesWallTile(int xPos, int yPos);
    void drawTile() override;
};
