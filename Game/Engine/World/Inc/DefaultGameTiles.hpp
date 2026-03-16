#pragma once

#include "GameTile.hpp"

class MetalGrillTile final : public CellTile
{
public:
    using CellTile::CellTile;
    void drawTile() override;
};

class MetalWallTile final : public CellTile
{
public:
    using CellTile::CellTile;
    void drawTile() override;
};

class MudWallTile final : public CellTile
{
public:
    using CellTile::CellTile;
    void drawTile() override;
};

class VinesWallTile final : public CellTile
{
public:
    using CellTile::CellTile;
    void drawTile() override;
};
