#pragma once

#include "Exceptions/Core/GameModeAlreadySetException.h"
#include <vector>

namespace Engine::Game
{
    class GameMode;
    class Entity;
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
        std::vector<Game::Entity*> m_Entities;

    private:
        EntityManager();
        ~EntityManager();

    public:
        static EntityManager* GetInstance();

    private:
        void Terminate();

    public:
        Game::GameMode* GetGameMode();

        // Instantiation methods
    private:
        template <typename T>
        T* InstantiateGameMode()
        {
            static_assert(std::is_base_of_v<Game::GameMode, T>, "The specified class does not derive Engine::Game::Entity");
            static_assert(std::is_default_constructible_v<T>, "The specified class does not implement a default constructor");

            if (m_GameMode) throw Exceptions::Core::GameModeAlreadySetException();

            T* instance = new T();
            m_GameMode = instance;
            return instance;
        }

        void DestroyGameMode();

    public:
        template <typename T>
        T* InstantiateEntity()
        {
            static_assert(std::is_base_of_v<Game::Entity, T>, "The specified class does not derive Engine::Game::Entity");
            static_assert(std::is_default_constructible_v<T>, "The specified class does not implement a default constructor");

            T* instance = new T();
            m_Entities.push_back(instance);
            return instance;
        }

        void DestroyEntity(const Game::Entity* entity);
    };
}
