﻿#pragma once
#include "IUpdatable.h"
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

    class Entity : public IUpdatable
    {
    private:
        friend class Core::EntityManager;

    private:
        std::vector<Component*> m_Components;

    protected:
        Entity(bool shouldUpdate);
        ~Entity() override = default;
    };
}
