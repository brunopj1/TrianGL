#pragma once

#include <unordered_set>
#include <vector>

namespace Engine
{
    // Forward declarations
    class Updatable;
    class Renderable;

    class EntityManager final
    {
    private:
        friend class Application;
        friend class GameMode;
        friend class Entity;
        friend class Component;

    private:
        inline static EntityManager* s_Instance = nullptr;

    private:
        GameMode* m_GameMode = nullptr;

        std::unordered_set<Entity*> m_Entities;
        std::unordered_set<Component*> m_Components;

        std::vector<Updatable*> m_OnUpdateQueue;
        std::vector<Updatable*> m_OnStartQueue;

        std::vector<Renderable*> m_RenderQueue;

    private:
        EntityManager();
        ~EntityManager();

    private:
        void Update(float deltaTime);
        void Render() const;

    private:
        static void SetGameMode(GameMode* gameMode);

        static void AddEntity(Entity* entity);
        static bool RemoveEntity(Entity* entity);

        static void AddComponent(Component* component);
        static bool RemoveComponent(Component* component);

    private:
        static GameMode* GetGameMode();
        static std::unordered_set<Entity*>& GetEntities();
        static std::unordered_set<Component*>& GetComponents();

    private:
        static void AddToQueue(Updatable* updatable, std::vector<Updatable*>& queue);
    };
}
