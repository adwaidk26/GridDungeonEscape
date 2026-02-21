#pragma once

#include "GameEntity.hpp"

class PlayerEntity final : public GameEntity
{
public:
    explicit PlayerEntity(Vector2 spawnPosition = {0.0f, 0.0f})
    {
        SetPosition(spawnPosition);
        SetMovable(true);
    }

    void Draw() override
    {
        DrawCircleV(position, 18.0f, SKYBLUE);
        DrawCircleLines(static_cast<int>(position.x), static_cast<int>(position.y), 18.0f, BLUE);
    }
};

class BoulderEntity final : public GameEntity
{
public:
    explicit BoulderEntity(Vector2 spawnPosition = {0.0f, 0.0f})
    {
        SetPosition(spawnPosition);
        SetMovable(true);
    }

    void Draw() override
    {
        DrawCircleV(position, 16.0f, GRAY);
        DrawCircleLines(static_cast<int>(position.x), static_cast<int>(position.y), 16.0f, DARKGRAY);
    }
};

class GemEntity final : public GameEntity
{
public:
    explicit GemEntity(Vector2 spawnPosition = {0.0f, 0.0f})
    {
        SetPosition(spawnPosition);
        SetCollectable(true);
    }

    void Draw() override
    {
        DrawPoly(position, 4, 14.0f, 45.0f, GOLD);
        DrawPolyLines(position, 4, 14.0f, 45.0f, ORANGE);
    }
};

class GrassEntity final : public GameEntity
{
public:
    explicit GrassEntity(Vector2 spawnPosition = {0.0f, 0.0f})
    {
        SetPosition(spawnPosition);
    }

    void Draw() override
    {
        DrawCircleV(position, 12.0f, LIME);
        DrawCircleLines(static_cast<int>(position.x), static_cast<int>(position.y), 12.0f, DARKGREEN);
    }
};

class StoneWallEntity final : public GameEntity
{
public:
    explicit StoneWallEntity(Vector2 spawnPosition = {0.0f, 0.0f})
    {
        SetPosition(spawnPosition);
    }

    void Draw() override
    {
        DrawRectangle(static_cast<int>(position.x - 12.0f), static_cast<int>(position.y - 12.0f), 24, 24, LIGHTGRAY);
        DrawRectangleLines(static_cast<int>(position.x - 12.0f), static_cast<int>(position.y - 12.0f), 24, 24, GRAY);
    }
};
