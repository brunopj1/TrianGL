#pragma once

#include "Internal/IUpdatable.h"
#include "Transform.h"
#include <vector>

// Forward declarations
namespace Engine::Core
{
    class EntityManager;
}

namespace Engine::Game
{
    // Forward declarations
    class Component;

    class Entity : public Internal::IUpdatable
    {
    private:
        friend class Core::EntityManager;

    private:
        Transform m_Transform;

    private:
        std::vector<Component*> m_Components;

    protected:
        Entity(bool shouldUpdate);
        ~Entity() override = default;

    public:
        Transform& GetTransform();
        const Transform& GetTransform() const;

        const std::vector<Component*>& GetComponents() const;
    };
}
