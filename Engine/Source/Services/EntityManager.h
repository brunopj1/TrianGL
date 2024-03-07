﻿#pragma once

#include "Exceptions/Core/GameModeAlreadySpecifiedException.h"
#include "Game/Entity.h"
#include "Util/Macros/SingletonMacros.hpp"
#include <vector>
#include <unordered_set>

// Forward declarations
namespace Engine::Core
{
    class Application;
}

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

namespace Engine::Services
{
    class EntityManager final
    {
    private:
        friend class Core::Application;
        friend class Game::GameMode;
        friend class Game::Entity;
        friend class Game::Component;

    private:
        inline static EntityManager* s_Instance = nullptr;
        DECLARE_SINGLETON_USAGE_VAR();

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
        void Update(float deltaTime);
        void Render() const;

    private:
        static void AddToQueue(Game::Internal::IUpdatable* updatable, std::vector<Game::Internal::IUpdatable*>& queue);

    public:
        static Game::GameMode* GetGameMode();

        // Instantiation methods (GameMode)
    private:
        template <typename T, typename... Args, typename = SINGLETON_TEMPLATE_SPAWN_CONDITION(Game::GameMode)>
        static T* CreateGameMode(Args&&... args) // NOLINT
        {
            DEBUG_SINGLETON_INSTANCE(s_Instance, "EntityManager");

            PREPARE_SINGLETON_USAGE(true);

            if (s_Instance->m_GameMode) throw Exceptions::Core::GameModeAlreadySpecifiedException();

            T* instance = new T(std::forward<Args>(args)...);
            s_Instance->m_GameMode = instance;

            PREPARE_SINGLETON_USAGE(false);

            return instance;
        }

        static void DestroyGameMode();

        // Instantiation methods (Entity)
    public:
        template <typename T, typename... Args, typename = SINGLETON_TEMPLATE_SPAWN_CONDITION_NO_ARGS(Game::Entity)>
        static T* SpawnEntity(Args&&... args)  // NOLINT
        {
            DEBUG_SINGLETON_INSTANCE(s_Instance, "EntityManager");

            PREPARE_SINGLETON_USAGE(true);

            T* instance = new T(std::forward<Args>(args)...);

            s_Instance->m_Entities.insert(instance);

            AddToQueue(instance, s_Instance->m_OnStartQueue);
            AddToQueue(instance, s_Instance->m_OnUpdateQueue);

            PREPARE_SINGLETON_USAGE(false);

            return instance;
        }

        static void DestroyEntity(Game::Entity* entity);

        // Instantiation methods (Component)
        template <typename T, typename... Args, typename = SINGLETON_TEMPLATE_SPAWN_CONDITION(Game::Component)>
        static T* AttachComponent(Game::Entity* parent, Args&&... args)  // NOLINT
        {
            DEBUG_SINGLETON_INSTANCE(s_Instance, "EntityManager");

            PREPARE_SINGLETON_USAGE(true);

            T* instance = new T(std::forward<Args>(args)...);

            s_Instance->m_Components.insert(instance);

            AddToQueue(instance, s_Instance->m_OnStartQueue);
            AddToQueue(instance, s_Instance->m_OnUpdateQueue);

            parent->m_Components.push_back(instance);
            instance->m_Parent = parent;

            if constexpr (std::is_base_of_v<Game::Internal::IRenderable, T>)
            {
                s_Instance->m_RenderQueue.push_back(instance);
            }

            PREPARE_SINGLETON_USAGE(false);

            return instance;
        }

        static void DetachComponent(Game::Component* component);

        // Entity lookup methods
        template <typename T, typename = SINGLETON_TEMPLATE_LOOKUP_CONDITION(Game::Entity)>
        static T* FindEntity()
        {
            DEBUG_SINGLETON_INSTANCE(s_Instance, "EntityManager");

            for (auto entity : s_Instance->m_Entities)
            {
                if (T* casted = dynamic_cast<T*>(entity))
                {
                    return casted;
                }
            }

            return nullptr;
        }

        template <typename T, typename = SINGLETON_TEMPLATE_LOOKUP_CONDITION(Game::Entity)>
        static std::vector<T*> FindEntities()
        {
            DEBUG_SINGLETON_INSTANCE(s_Instance, "EntityManager");

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
        template <typename T, typename = SINGLETON_TEMPLATE_LOOKUP_CONDITION(Game::Component)>
        static T* FindComponent()
        {
            DEBUG_SINGLETON_INSTANCE(s_Instance, "EntityManager");

            for (auto component : s_Instance->m_Components)
            {
                if (T* casted = dynamic_cast<T*>(component))
                {
                    return casted;
                }
            }

            return nullptr;
        }

        template <typename T, typename = SINGLETON_TEMPLATE_LOOKUP_CONDITION(Game::Component)>
        static std::vector<T*> FindComponents()
        {
            DEBUG_SINGLETON_INSTANCE(s_Instance, "EntityManager");

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

        template <typename T, typename = SINGLETON_TEMPLATE_LOOKUP_CONDITION(Game::Component)>
        static T* FindComponentInEntity(Game::Entity* entity)
        {
            DEBUG_SINGLETON_INSTANCE(s_Instance, "EntityManager");

            for (auto component : entity->m_Components)
            {
                if (T* casted = dynamic_cast<T*>(component))
                {
                    return casted;
                }
            }

            return nullptr;
        }

        template <typename T, typename = SINGLETON_TEMPLATE_LOOKUP_CONDITION(Game::Component)>
        static std::vector<T*> FindComponentsInEntity(Game::Entity* entity)
        {
            DEBUG_SINGLETON_INSTANCE(s_Instance, "EntityManager");

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