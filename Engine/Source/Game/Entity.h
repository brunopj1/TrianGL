#pragma once

#include "Internal/Updatable.h"
#include "Transform.h"
#include <vector>

// Forward declarations
namespace Engine::Services
{
    class EntityManager;
}

namespace Engine::Game
{
    // Forward declarations
    class Component;

    class Entity : public Internal::Updatable
    {
    private:
        friend class Services::EntityManager;

    private:
        Transform m_Transform;

    private:
        std::vector<Component*> m_Components;

    protected:
        Entity(bool shouldUpdate);
        ~Entity() override;

    public:
        Transform& GetTransform();
        const Transform& GetTransform() const;

        const std::vector<Component*>& GetComponents() const;
    };
}
