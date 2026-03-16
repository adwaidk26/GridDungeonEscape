#include "DefaultGameTiles.hpp"

#include "RenderUtils.hpp"

namespace {

Texture2D& GetMetalGrillTexture()
{
    static Texture2D texture = LoadTexture(TextFormat("%s/MetalGrilTile.png", IMAGE_FOLDER));
    return texture;
}

Texture2D& GetMetalWallTexture()
{
    static Texture2D texture = LoadTexture(TextFormat("%s/MetalWallTile.png", IMAGE_FOLDER));
    return texture;
}

Texture2D& GetMudWallTexture()
{
    static Texture2D texture = LoadTexture(TextFormat("%s/MudWallTile.png", IMAGE_FOLDER));
    return texture;
}

Texture2D& GetVinesWallTexture()
{
    static Texture2D texture = LoadTexture(TextFormat("%s/VinesWallTile.png", IMAGE_FOLDER));
    return texture;
}

}  // namespace

MetalGrillTile::MetalGrillTile(int xPos, int yPos)
    : CellTile(xPos, yPos)
{
}

MetalWallTile::MetalWallTile(int xPos, int yPos)
    : CellTile(xPos, yPos)
{
}

MudWallTile::MudWallTile(int xPos, int yPos)
    : CellTile(xPos, yPos)
{
    setTileDestructible(true);
}

VinesWallTile::VinesWallTile(int xPos, int yPos)
    : CellTile(xPos, yPos)
{
    setTileClimbable(true);
}

void MetalGrillTile::drawTile()
{
    RenderUtils::DrawTextureInTile(GetMetalGrillTexture(), getTilePosition());
}

void MetalWallTile::drawTile()
{
    RenderUtils::DrawTextureInTile(GetMetalWallTexture(), getTilePosition());
}

void MudWallTile::drawTile()
{
    RenderUtils::DrawTextureInTile(GetMudWallTexture(), getTilePosition());
}

void VinesWallTile::drawTile()
{
    RenderUtils::DrawTextureInTile(GetVinesWallTexture(), getTilePosition());
}
