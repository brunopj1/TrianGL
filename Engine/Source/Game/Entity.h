#pragma once

#include "Object.h"
#include "Transform.h"
#include "Core/EntityManager.h"
#include "Util/Macros/SpawnerMacros.hpp"
#include <ranges>
#include <vector>

namespace TGL
{
    class Entity : public Object
    {
    private:
        friend class EntityManager;
        friend class Component;

    private:
        Transform m_Transform;
        std::vector<Component*> m_Components;

    protected:
        Entity(bool shouldUpdate);
        ~Entity() override;

    public:
        Transform& GetTransform();
        const Transform& GetTransform() const;

    public:
        void Destroy();

    public:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::Component)>
        T* AttachComponent(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            return EntityManager::CreateComponent<T>(this, std::forward<Args>(args)...);
        }

        void DetachAllComponents() const;

    public:
        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(TGL::Component)>
        T* FindComponent()
        {
            return EntityManager::FindComponentInEntity<T>(m_Components);
        }

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(TGL::Component)>
        std::vector<T*> FindComponents()
        {
            return EntityManager::FindComponentsInEntity<T>(m_Components);
        }
    };
}
