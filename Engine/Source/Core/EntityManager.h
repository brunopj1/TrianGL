#pragma once

#include "../Exceptions/Core/GameModeAlreadySpecifiedException.h"
#include "Game/Entity.h"
#include <vector>
#include <unordered_set>

namespace Engine::Game
{
    class GameMode;
    class IUpdatable;
    class Entity;
    class Component;
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

        std::vector<Game::IUpdatable*> m_OnUpdateQueue;
        std::vector<Game::IUpdatable*> m_OnStartQueue;

    private:
        EntityManager();
        ~EntityManager();

    public:
        static EntityManager* GetInstance();

    private:
        void Update();
        void Render() const;

    private:
        static void AddToQueue(Game::IUpdatable* updatable, std::vector<Game::IUpdatable*>& queue);

    public:
        Game::GameMode* GetGameMode() const;

        // Instantiation methods (GameMode)
    private:
        template <typename T>
        T* CreateGameMode()
        {
            static_assert(std::is_base_of_v<Game::GameMode, T>, "The specified class does not derive Engine::Game::Entity");
            static_assert(std::is_default_constructible_v<T>, "The specified class does not implement a default constructor");

            if (m_GameMode) throw Exceptions::Core::GameModeAlreadySpecifiedException();

            T* instance = new T();
            m_GameMode = instance;
            return instance;
        }

        void DestroyGameMode();

        // Instantiation methods (Entity)
    public:
        template <typename T>
        T* CreateEntity()
        {
            static_assert(std::is_base_of_v<Game::Entity, T>, "The specified class does not derive Engine::Game::Entity");
            static_assert(std::is_default_constructible_v<T>, "The specified class does not implement a default constructor");

            T* instance = new T();

            m_Entities.insert(instance);

            AddToQueue(instance, m_OnStartQueue);
            AddToQueue(instance, m_OnUpdateQueue);

            return instance;
        }

        void DestroyEntity(Game::Entity* entity);

        // Instantiation methods (Component)
        template <typename T>
        T* AttachComponent(Game::Entity* parent)
        {
            static_assert(std::is_base_of_v<Game::Component, T>, "The specified class does not derive Engine::Game::Component");
            static_assert(std::is_default_constructible_v<T>, "The specified class does not implement a default constructor");

            T* instance = new T();

            m_Components.insert(instance);

            AddToQueue(instance, m_OnStartQueue);
            AddToQueue(instance, m_OnUpdateQueue);

            parent->m_Components.push_back(instance);
            instance->m_Parent = parent;

            return instance;
        }

        void DetachComponent(Game::Component* component);
    };
}
