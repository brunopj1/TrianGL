#pragma once

#include "Internal/Updatable.h"
#include <type_traits>

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

    public:
        template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
        T* As()
        {
            return dynamic_cast<T*>(this);
        }
    };
}
