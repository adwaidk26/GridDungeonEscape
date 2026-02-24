#pragma once

#include <cstdint>
#include <raylib.h>

#include "GameConstants.hpp"

enum class GameEntityTrait : uint32_t
{
    None = 0,
    Movable = 1u << 0,
    Collectable = 1u << 1,
    Breakable = 1u << 2,
    Collector = 1u << 3
};

class GameEntity
{
public:
    virtual ~GameEntity() = default;

    void SetPosition(float x, float y);
    void SetPosition(Vector2 pos);
    Vector2 GetPosition() const;

    void SetGridPosition(int x, int y);
    int GetGridX() const;
    int GetGridY() const;

    static Vector2 GetWorldPosFromGridPos(int x, int y);

    void AddTrait(GameEntityTrait trait);
    void RemoveTrait(GameEntityTrait trait);
    bool HasTrait(GameEntityTrait trait) const;

    void SetMovable(bool enabled);
    void SetCollectable(bool enabled);
    void SetBreakable(bool enabled);
    void SetCollector(bool enabled);

    bool IsMovable() const;
    bool IsCollectable() const;
    bool IsBreakable() const;
    bool IsCollector() const;

    virtual void Draw() = 0;

protected:
    Vector2 position{0.0f, 0.0f};
    int gridX = 0;
    int gridY = 0;
    uint32_t traits = static_cast<uint32_t>(GameEntityTrait::None);
};

inline void GameEntity::SetPosition(float x, float y)
{
    position = {x, y};
}

inline void GameEntity::SetPosition(Vector2 pos)
{
    position = pos;
}

inline Vector2 GameEntity::GetPosition() const
{
    return position;
}

inline void GameEntity::SetGridPosition(int x, int y)
{
    gridX = x;
    gridY = y;
}

inline int GameEntity::GetGridX() const
{
    return gridX;
}

inline int GameEntity::GetGridY() const
{
    return gridY;
}

inline Vector2 GameEntity::GetWorldPosFromGridPos(int x, int y)
{
    return {
        static_cast<float>(x * GameConstants::TILE_SIZE + GameConstants::TILE_SIZE / 2),
        static_cast<float>(y * GameConstants::TILE_SIZE + GameConstants::TILE_SIZE / 2)
    };
}

inline void GameEntity::AddTrait(GameEntityTrait trait)
{
    traits |= static_cast<uint32_t>(trait);
}

inline void GameEntity::RemoveTrait(GameEntityTrait trait)
{
    traits &= ~static_cast<uint32_t>(trait);
}

inline bool GameEntity::HasTrait(GameEntityTrait trait) const
{
    return (traits & static_cast<uint32_t>(trait)) != 0u;
}

inline void GameEntity::SetMovable(bool enabled)
{
    if (enabled) {
        AddTrait(GameEntityTrait::Movable);
    } else {
        RemoveTrait(GameEntityTrait::Movable);
    }
}

inline void GameEntity::SetCollectable(bool enabled)
{
    if (enabled) {
        AddTrait(GameEntityTrait::Collectable);
    } else {
        RemoveTrait(GameEntityTrait::Collectable);
    }
}

inline void GameEntity::SetBreakable(bool enabled)
{
    if (enabled) {
        AddTrait(GameEntityTrait::Breakable);
    } else {
        RemoveTrait(GameEntityTrait::Breakable);
    }
}

inline void GameEntity::SetCollector(bool enabled)
{
    if (enabled) {
        AddTrait(GameEntityTrait::Collector);
    } else {
        RemoveTrait(GameEntityTrait::Collector);
    }
}

inline bool GameEntity::IsMovable() const
{
    return HasTrait(GameEntityTrait::Movable);
}

inline bool GameEntity::IsCollectable() const
{
    return HasTrait(GameEntityTrait::Collectable);
}

inline bool GameEntity::IsBreakable() const
{
    return HasTrait(GameEntityTrait::Breakable);
}

inline bool GameEntity::IsCollector() const
{
    return HasTrait(GameEntityTrait::Collector);
}
