#pragma once

#include "Internal/IUpdatable.h"

namespace Engine::Services
{
    class EntityManager;
}

namespace Engine::Game
{
    // Forward declarations
    class Entity;

    class Component : public Internal::IUpdatable
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
