#pragma once

#include <unordered_map>
#include <vector>

namespace TGL
{
    // Forward declarations
    class IdGenerator;
    class Updatable;
    class Renderable;

    template <typename T, typename C>
    class LazyPtr;

    class EntityManager final
    {
    private:
        friend class Application;
        friend class GameMode;
        friend class Entity;
        friend class Component;

        template <typename T, typename C>
        friend class LazyPtr;

    private:
        inline static EntityManager* s_Instance = nullptr;

    private:
        IdGenerator* m_IdGenerator;

    private:
        GameMode* m_GameMode = nullptr;

        std::unordered_map<uint32_t, Entity*> m_Entities;
        std::unordered_map<uint32_t, Component*> m_Components;

        std::vector<Updatable*> m_OnUpdateQueue;
        std::vector<Updatable*> m_OnStartQueue;

        std::vector<Renderable*> m_RenderQueue;

    private:
        EntityManager(IdGenerator* idGenerator);
        ~EntityManager();

    private:
        void Update(float deltaTime);
        void Render() const;

    private:
        static void SetGameMode(GameMode* gameMode);

        static void AddEntity(Entity* entity);
        static Entity* GetEntity(uint32_t id);
        static bool RemoveEntity(Entity* entity);

        static void AddComponent(Component* component);
        static Component* GetComponent(uint32_t id);
        static bool RemoveComponent(Component* component);

    private:
        static GameMode* GetGameMode();
        static std::unordered_map<uint32_t, Entity*>& GetEntities();
        static std::unordered_map<uint32_t, Component*>& GetComponents();

    private:
        static void AddToQueue(Updatable* updatable, std::vector<Updatable*>& queue);
    };
}
