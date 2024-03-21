#pragma once

#include "Object.h"
#include "Base/Updatable.h"
#include "Transform.h"
#include "Core/EntityManager.h"
#include "Util/Macros/SpawnerMacros.hpp"
#include <ranges>
#include <vector>

namespace TGL
{
    // Forward declarations
    class Component;

    template <typename T, typename C>
    class LazyPtr;

    class Entity : public Object, public Updatable
    {
    private:
        friend class Component;

        template <typename T, typename C>
        friend class LazyPtr;

    private:
        DECLARE_SPAWNER_USAGE_VAR();

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
        template <typename T, typename = std::enable_if_t<std::is_base_of_v<Entity, T>>>
        T* As()
        {
            return dynamic_cast<T*>(this);
        }

    public:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::Entity)>
        static T* SpawnEntity(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            PREPARE_SPAWNER_USAGE(TGL::Entity);

            T* instance = new T(std::forward<Args>(args)...);

            EntityManager::AddEntity(instance);

            return instance;
        }

        void Destroy();

    public:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::Component)>
        T* AttachComponent(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            // Cannot use the macro directly because of circular dependencies
#ifdef DEBUG
            PrepareComponentSpawnerUsage();
#endif

            T* instance = new T(std::forward<Args>(args)...);

            EntityManager::AddComponent(instance);

            m_Components.push_back(instance);
            instance->m_Parent = this;

            return instance;
        }

        void DetachAllComponents() const;

    public:
        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(Entity)>
        static T* FindEntityGlobally()
        {
            for (auto entity : EntityManager::GetEntities())
            {
                if (T* casted = dynamic_cast<T*>(entity))
                {
                    return casted;
                }
            }

            return nullptr;
        }

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(Entity)>
        static std::vector<T*> FindEntitiesGlobally()
        {
            std::vector<T*> entities;

            for (auto entity : EntityManager::GetEntities() | std::views::values)
            {
                if (T* casted = dynamic_cast<T*>(entity))
                {
                    entities.push_back(casted);
                }
            }

            return entities;
        }

        // Component lookup methods
        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(Component)>
        static T* FindComponentGlobally()
        {
            for (auto component : EntityManager::GetComponents() | std::views::values)
            {
                if (T* casted = dynamic_cast<T*>(component))
                {
                    return casted;
                }
            }

            return nullptr;
        }

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(Component)>
        static std::vector<T*> FindComponentsGlobally()
        {
            std::vector<T*> components;

            for (auto component : EntityManager::GetComponents())
            {
                if (T* casted = dynamic_cast<T*>(component))
                {
                    components.push_back(casted);
                }
            }

            return components;
        }

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(Component)>
        T* FindComponent()
        {
            for (auto component : m_Components)
            {
                if (T* casted = dynamic_cast<T*>(component))
                {
                    return casted;
                }
            }

            return nullptr;
        }

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(Component)>
        std::vector<T*> FindComponents()
        {
            std::vector<T*> components;

            for (auto component : m_Components)
            {
                if (T* casted = dynamic_cast<T*>(component))
                {
                    components.push_back(casted);
                }
            }

            return components;
        }

#ifdef DEBUG

    private:
        static void PrepareComponentSpawnerUsage();
#endif
    };
}
