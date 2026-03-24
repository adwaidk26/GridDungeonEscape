#pragma once

#include "GameEntity.hpp"
#include "RenderUtils.hpp"

namespace DefaultGameEntityTextures {

inline Texture2D& GetBoulderEntityTexture()
{
    static Texture2D texture = LoadTexture(TextFormat("%s/BoulderEntity.png", IMAGE_FOLDER));
    return texture;
}

inline Texture2D& GetPlayerEntityTexture()
{
    static Texture2D texture = LoadTexture(TextFormat("%s/PlayerRightEntity.png", IMAGE_FOLDER));
    return texture;
}

inline Texture2D& GetGemEntityTexture()
{
    static Texture2D texture = LoadTexture(TextFormat("%s/GemEntity.png", IMAGE_FOLDER));
    return texture;
}

inline Texture2D& GetGrassBushEntityTexture()
{
    static Texture2D texture = LoadTexture(TextFormat("%s/GrassBushEntity.png", IMAGE_FOLDER));
    return texture;
}

inline Texture2D& GetStoneWallEntitiyTexture()
{
    static Texture2D texture = LoadTexture(TextFormat("%s/StoneWallEnitity.png", IMAGE_FOLDER));
    return texture;
}
}  // namespace DefaultGameEntityTextures

class PlayerEntity final : public GameEntity
{
public:
    explicit PlayerEntity(Vector2 spawnPosition = {0.0f, 0.0f})
    {
        SetPosition(spawnPosition);
        SetMovable(true);
        SetCollector(true);
        SetGravityApplicable(false);
    }

    void Draw() override
    {
        RenderUtils::DrawTextureInTile(DefaultGameEntityTextures::GetPlayerEntityTexture(), position);
    }
};

class BoulderEntity final : public GameEntity
{
public:
    explicit BoulderEntity(Vector2 spawnPosition = {0.0f, 0.0f})
    {
        SetPosition(spawnPosition);
        SetMovable(true);
        SetGravityApplicable(true);
    }

    void Draw() override
    {
        RenderUtils::DrawTextureInTile(DefaultGameEntityTextures::GetBoulderEntityTexture(), position);
    }
};

class GemEntity final : public GameEntity
{
public:
    explicit GemEntity(Vector2 spawnPosition = {0.0f, 0.0f})
    {
        SetPosition(spawnPosition);
        SetCollectable(true);
        SetGravityApplicable(false);
    }

    void Draw() override
    {
        RenderUtils::DrawTextureInTile(DefaultGameEntityTextures::GetGemEntityTexture(), position);
    }
};

class GrassEntity final : public GameEntity
{
public:
    explicit GrassEntity(Vector2 spawnPosition = {0.0f, 0.0f})
    {
        SetPosition(spawnPosition);
        SetCollectable(true);
        SetGravityApplicable(false);
    }

    void Draw() override
    {
        RenderUtils::DrawTextureInTile(DefaultGameEntityTextures::GetGrassBushEntityTexture(), position);
    }
};

class StoneWallEntity final : public GameEntity
{
public:
    explicit StoneWallEntity(Vector2 spawnPosition = {0.0f, 0.0f})
    {
        SetPosition(spawnPosition);
        SetGravityApplicable(false);
    }

    void Draw() override
    {
        RenderUtils::DrawTextureInTile(DefaultGameEntityTextures::GetStoneWallEntitiyTexture(), position);

    }
};
