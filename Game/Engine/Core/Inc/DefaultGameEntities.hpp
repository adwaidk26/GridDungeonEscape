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
