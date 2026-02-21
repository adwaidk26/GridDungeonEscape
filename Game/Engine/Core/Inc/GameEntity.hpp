#pragma once

#include <cstdint>
#include <raylib.h>

enum class GameEntityTrait : uint32_t
{
    None = 0,
    Movable = 1u << 0,
    Collectable = 1u << 1,
    Breakable = 1u << 2
};

class GameEntity
{
public:
    virtual ~GameEntity() = default;

    void SetPosition(float x, float y);
    void SetPosition(Vector2 pos);
    Vector2 GetPosition() const;

    void AddTrait(GameEntityTrait trait);
    void RemoveTrait(GameEntityTrait trait);
    bool HasTrait(GameEntityTrait trait) const;

    void SetMovable(bool enabled);
    void SetCollectable(bool enabled);
    void SetBreakable(bool enabled);

    bool IsMovable() const;
    bool IsCollectable() const;
    bool IsBreakable() const;

    virtual void Draw() = 0;

protected:
    Vector2 position{0.0f, 0.0f};
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
