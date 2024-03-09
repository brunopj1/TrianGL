#pragma once

#include "Internal/Updatable.h"
#include "Transform.h"
#include <vector>

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

    public:
        template <typename T, typename = std::enable_if_t<std::is_base_of_v<Entity, T>>>
        T* As()
        {
            return dynamic_cast<T*>(this);
        }
    };
}
