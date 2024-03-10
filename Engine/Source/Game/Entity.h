#pragma once

#include "Internal/Updatable.h"
#include "Transform.h"
#include "Services/EntityManager.h"
#include "Util/Macros/SpawnerMacros.hpp"
#include <vector>

namespace Engine::Game
{
    // Forward declarations
    class Component;

    class Entity : public Internal::Updatable
    {
    private:
        friend class Component;

    private:
        DECLARE_SPAWNER_USAGE_VAR();

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

    public:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(Engine::Game::Entity)>
        static T* SpawnEntity(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            PREPARE_SPAWNER_USAGE();

            T* instance = new T(std::forward<Args>(args)...);

            Services::EntityManager::AddEntity(instance);

            return instance;
        }

        void Destroy();

    public:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(Engine::Game::Component)>
        T* AttachComponent(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            PREPARE_SPAWNER_USAGE();

            T* instance = new T(std::forward<Args>(args)...);

            Services::EntityManager::AddComponent(instance);

            m_Components.push_back(instance);
            instance->m_Parent = this;

            return instance;
        }

        void DetachComponent(Component* component);
        void DetachComponents(const std::vector<Component*>& components);
        void DetachAllComponents();

    public:
        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(Game::Entity)>
        static T* FindEntityGlobally()
        {
            for (auto entity : Services::EntityManager::GetEntities())
            {
                if (T* casted = dynamic_cast<T*>(entity))
                {
                    return casted;
                }
            }

            return nullptr;
        }

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(Game::Entity)>
        static std::vector<T*> FindEntitiesGlobally()
        {
            std::vector<T*> entities;

            for (auto entity : Services::EntityManager::GetEntities())
            {
                if (T* casted = dynamic_cast<T*>(entity))
                {
                    entities.push_back(casted);
                }
            }

            return entities;
        }

        // Component lookup methods
        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(Game::Component)>
        static T* FindComponentGlobally()
        {
            for (auto component : Services::EntityManager::GetComponents())
            {
                if (T* casted = dynamic_cast<T*>(component))
                {
                    return casted;
                }
            }

            return nullptr;
        }

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(Game::Component)>
        static std::vector<T*> FindComponentsGlobally()
        {
            std::vector<T*> components;

            for (auto component : Services::EntityManager::GetComponents())
            {
                if (T* casted = dynamic_cast<T*>(component))
                {
                    components.push_back(casted);
                }
            }

            return components;
        }

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(Game::Component)>
        T* FindComponentInEntity()
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

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(Game::Component)>
        std::vector<T*> FindComponentsInEntity()
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
    };
}
