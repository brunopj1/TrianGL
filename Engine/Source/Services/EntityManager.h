#pragma once

#include "Game/Entity.h"
#include <unordered_set>
#include <vector>

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
    class Updatable;
    class Renderable;
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

    private:
        Game::GameMode* m_GameMode = nullptr;

        std::unordered_set<Game::Entity*> m_Entities;
        std::unordered_set<Game::Component*> m_Components;

        std::vector<Game::Internal::Updatable*> m_OnUpdateQueue;
        std::vector<Game::Internal::Updatable*> m_OnStartQueue;

        std::vector<Game::Internal::Renderable*> m_RenderQueue;

    private:
        EntityManager();
        ~EntityManager();

    private:
        void Update(float deltaTime);
        void Render() const;

    private:
        static void SetGameMode(Game::GameMode* gameMode);

        static void AddEntity(Game::Entity* entity);
        static void RemoveEntity(Game::Entity* entity);

        static void AddComponent(Game::Component* component);
        static void RemoveComponent(Game::Component* component);

    private:
        static Game::GameMode* GetGameMode();
        static std::unordered_set<Game::Entity*>& GetEntities();
        static std::unordered_set<Game::Component*>& GetComponents();

    private:
        static void AddToQueue(Game::Internal::Updatable* updatable, std::vector<Game::Internal::Updatable*>& queue);
    };
}
