#pragma once

#include "Internal/Updatable.h"

namespace Engine::Services
{
    class EntityManager;
}

namespace Engine::Game
{
    // Forward declarations
    class Entity;

    class Component : public Internal::Updatable
    {
    private:
        friend class Services::EntityManager;

    private:
        Entity* m_Parent = nullptr;

    protected:
        Component(bool shouldUpdate);
        ~Component() override;

    public:
        Entity* GetParent() const;
    };
}
