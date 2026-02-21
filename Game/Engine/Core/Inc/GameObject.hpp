#pragma once

#include <cstdint>
#include <raylib.h>

enum class GameObjectTrait : uint32_t
{
    None = 0,
    Movable = 1u << 0,
    Collectable = 1u << 1,
    Breakable = 1u << 2
};

class GameObject
{
public:
    virtual ~GameObject() = default;

    void SetPosition(float x, float y);
    void SetPosition(Vector2 pos);
    Vector2 GetPosition() const;

    void AddTrait(GameObjectTrait trait);
    void RemoveTrait(GameObjectTrait trait);
    bool HasTrait(GameObjectTrait trait) const;

    void SetMovable(bool enabled);
    void SetCollectable(bool enabled);
    void SetBreakable(bool enabled);

    bool IsMovable() const;
    bool IsCollectable() const;
    bool IsBreakable() const;

    virtual void Draw() = 0;

protected:
    Vector2 position{0.0f, 0.0f};
    uint32_t traits = static_cast<uint32_t>(GameObjectTrait::None);
};

inline void GameObject::SetPosition(float x, float y)
{
    position = {x, y};
}

inline void GameObject::SetPosition(Vector2 pos)
{
    position = pos;
}

inline Vector2 GameObject::GetPosition() const
{
    return position;
}

inline void GameObject::AddTrait(GameObjectTrait trait)
{
    traits |= static_cast<uint32_t>(trait);
}

inline void GameObject::RemoveTrait(GameObjectTrait trait)
{
    traits &= ~static_cast<uint32_t>(trait);
}

inline bool GameObject::HasTrait(GameObjectTrait trait) const
{
    return (traits & static_cast<uint32_t>(trait)) != 0u;
}

inline void GameObject::SetMovable(bool enabled)
{
    if (enabled) {
        AddTrait(GameObjectTrait::Movable);
    } else {
        RemoveTrait(GameObjectTrait::Movable);
    }
}

inline void GameObject::SetCollectable(bool enabled)
{
    if (enabled) {
        AddTrait(GameObjectTrait::Collectable);
    } else {
        RemoveTrait(GameObjectTrait::Collectable);
    }
}

inline void GameObject::SetBreakable(bool enabled)
{
    if (enabled) {
        AddTrait(GameObjectTrait::Breakable);
    } else {
        RemoveTrait(GameObjectTrait::Breakable);
    }
}

inline bool GameObject::IsMovable() const
{
    return HasTrait(GameObjectTrait::Movable);
}

inline bool GameObject::IsCollectable() const
{
    return HasTrait(GameObjectTrait::Collectable);
}

inline bool GameObject::IsBreakable() const
{
    return HasTrait(GameObjectTrait::Breakable);
}
