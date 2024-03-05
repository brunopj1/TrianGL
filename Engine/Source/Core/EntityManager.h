#pragma once

#include "Exceptions/Core/GameModeAlreadySpecifiedException.h"
#include "Game/Entity.h"
#include "Util/DebugFeatures.hpp"
#include <vector>
#include <unordered_set>

// Forward declarations
namespace Engine::Game
{
    class GameMode;
    class Entity;
    class Component;
}

namespace Engine::Game::Internal
{
    class IUpdatable;
    class IRenderable;
}

namespace Engine::Core
{
    class EntityManager final
    {
    private:
        friend class Application;

    private:
        inline static EntityManager* s_Instance = nullptr;

    private:
        Game::GameMode* m_GameMode = nullptr;

        std::unordered_set<Game::Entity*> m_Entities;
        std::unordered_set<Game::Component*> m_Components;

        std::vector<Game::Internal::IUpdatable*> m_OnUpdateQueue;
        std::vector<Game::Internal::IUpdatable*> m_OnStartQueue;

        std::vector<Game::Internal::IRenderable*> m_RenderQueue;

    private:
        EntityManager();
        ~EntityManager();

    private:
        static void InitializeComponents();
        static void TerminateComponents();

    private:
        void Update();
        void Render() const;

    private:
        static void AddToQueue(Game::Internal::IUpdatable* updatable, std::vector<Game::Internal::IUpdatable*>& queue);

    public:
        Game::GameMode* GetGameMode() const;

        // Instantiation methods (GameMode)
    private:
        template <typename T>
        static T* CreateGameMode()
        {
            DEBUG_SINGLETON(s_Instance, "EntityManager");

            static_assert(std::is_base_of_v<Game::GameMode, T>, "The specified class does not derive Engine::Game::Entity");
            static_assert(std::is_constructible_v<T>, "The specified class does not implement a default constructor");

            if (s_Instance->m_GameMode) throw Exceptions::Core::GameModeAlreadySpecifiedException();

            T* instance = new T();
            s_Instance->m_GameMode = instance;
            return instance;
        }

        static void DestroyGameMode();

        // Instantiation methods (Entity)
    public:
        template <typename T>
        static T* SpawnEntity()
        {
            DEBUG_SINGLETON(s_Instance, "EntityManager");

            static_assert(std::is_base_of_v<Game::Entity, T>, "The specified class does not derive Engine::Game::Entity");
            static_assert(std::is_constructible_v<T>, "The specified class does not implement a default constructor");

            T* instance = new T();

            s_Instance->m_Entities.insert(instance);

            AddToQueue(instance, s_Instance->m_OnStartQueue);
            AddToQueue(instance, s_Instance->m_OnUpdateQueue);

            return instance;
        }

        static void DestroyEntity(Game::Entity* entity);

        // Instantiation methods (Component)
        template <typename T>
        static T* AttachComponent(Game::Entity* parent)
        {
            DEBUG_SINGLETON(s_Instance, "EntityManager");

            static_assert(std::is_base_of_v<Game::Component, T>, "The specified class does not derive Engine::Game::Component");
            static_assert(std::is_constructible_v<T>, "The specified class does not implement a default constructor");

            T* instance = new T();

            s_Instance->m_Components.insert(instance);

            AddToQueue(instance, s_Instance->m_OnStartQueue);
            AddToQueue(instance, s_Instance->m_OnUpdateQueue);

            parent->m_Components.push_back(instance);
            instance->m_Parent = parent;

            if constexpr (std::is_base_of_v<Game::Internal::IRenderable, T>)
            {
                s_Instance->m_RenderQueue.push_back(instance);
            }

            return instance;
        }

        static void DetachComponent(Game::Component* component);

        // Entity lookup methods
        template <typename T>
        static T* FindEntity()
        {
            DEBUG_SINGLETON(s_Instance, "EntityManager");

            static_assert(std::is_base_of_v<Game::Entity, T>, "The specified class does not derive Engine::Game::Entity");

            for (auto entity : s_Instance->m_Entities)
            {
                if (T* casted = dynamic_cast<T*>(entity))
                {
                    return casted;
                }
            }

            return nullptr;
        }

        template <typename T>
        static std::vector<T*> FindEntities()
        {
            DEBUG_SINGLETON(s_Instance, "EntityManager");

            static_assert(std::is_base_of_v<Game::Entity, T>, "The specified class does not derive Engine::Game::Entity");

            std::vector<T*> entities;

            for (auto entity : s_Instance->m_Entities)
            {
                if (T* casted = dynamic_cast<T*>(entity))
                {
                    entities.push_back(casted);
                }
            }

            return entities;
        }

        // Component lookup methods
        template <typename T>
        static T* FindComponent()
        {
            DEBUG_SINGLETON(s_Instance, "EntityManager");

            static_assert(std::is_base_of_v<Game::Component, T>, "The specified class does not derive Engine::Game::Component");

            for (auto component : s_Instance->m_Components)
            {
                if (T* casted = dynamic_cast<T*>(component))
                {
                    return casted;
                }
            }

            return nullptr;
        }

        template <typename T>
        static std::vector<T*> FindComponents()
        {
            DEBUG_SINGLETON(s_Instance, "EntityManager");

            static_assert(std::is_base_of_v<Game::Component, T>, "The specified class does not derive Engine::Game::Component");

            std::vector<T*> components;

            for (auto component : s_Instance->m_Components)
            {
                if (T* casted = dynamic_cast<T*>(component))
                {
                    components.push_back(casted);
                }
            }

            return components;
        }

        template <typename T>
        static T* FindComponentInEntity(Game::Entity* entity)
        {
            DEBUG_SINGLETON(s_Instance, "EntityManager");

            static_assert(std::is_base_of_v<Game::Component, T>, "The specified class does not derive Engine::Game::Component");

            for (auto component : entity->m_Components)
            {
                if (T* casted = dynamic_cast<T*>(component))
                {
                    return casted;
                }
            }

            return nullptr;
        }

        template <typename T>
        static std::vector<T*> FindComponentsInEntity(Game::Entity* entity)
        {
            DEBUG_SINGLETON(s_Instance, "EntityManager");

            static_assert(std::is_base_of_v<Game::Component, T>, "The specified class does not derive Engine::Game::Component");

            std::vector<T*> components;

            for (auto component : entity->m_Components)
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
