#pragma once

#include "IUpdatable.h"

namespace Engine::Core
{
    class EntityManager;
}

namespace Engine::Game
{
    // Forward declarations
    class Entity;

    class Component : public IUpdatable
    {
    private:
        friend class Core::EntityManager;

    private:
        Entity* m_Parent = nullptr;

    protected:
        Component(bool shouldUpdate);
        ~Component() override = default;

    public:
        Entity* GetParent() const;
    };
}
