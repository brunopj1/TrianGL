#pragma once

#include <vector>
#include <unordered_map>

#include "Game/Base/ImGuiMenuRender.h"
#include "Util/Macros/SingletonMacros.hpp"

namespace TGL
{
    // Forward declarations
    class IdGenerator;
    class Updatable;
    class Renderable;

#ifdef DEBUG
    class ImGuiRenderer;
    class ImGuiMenuRenderer;
#endif

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
        DECLARE_SINGLETON_INSTANCE_VAR(TGL::EntityManager);

    private:
        IdGenerator* m_IdGenerator;

    private:
        GameMode* m_GameMode = nullptr;

        std::unordered_map<uint64_t, Entity*> m_Entities;
        std::unordered_map<uint64_t, Component*> m_Components;

        std::vector<Updatable*> m_OnUpdateQueue;
        std::vector<Updatable*> m_OnStartQueue;

        std::vector<Renderable*> m_RenderQueue;

#ifdef DEBUG
        std::vector<ImGuiRenderer*> m_ImGuiRenderQueue;
        std::vector<ImGuiMenuRenderer*> m_ImGuiMenuRenderQueue;
#endif

    private:
        EntityManager(IdGenerator* idGenerator);
        ~EntityManager();

    private:
        void Update(float deltaTime);
        void Render() const;

    private:
        static void SetGameMode(GameMode* gameMode);

        static void AddEntity(Entity* entity);
        static Entity* GetEntity(uint64_t id);
        static bool RemoveEntity(Entity* entity);

        static void AddComponent(Component* component);
        static Component* GetComponent(uint64_t id);
        static bool RemoveComponent(Component* component);

    private:
        static GameMode* GetGameMode();
        static std::unordered_map<uint64_t, Entity*>& GetEntities();
        static std::unordered_map<uint64_t, Component*>& GetComponents();

        static size_t GetEntityCount();
        static size_t GetComponentCount();

    private:
        static void AddToQueue(Updatable* updatable, std::vector<Updatable*>& queue);

#ifdef DEBUG
        static void AddToRenderQueue(ImGuiMenuRenderer* renderer, std::vector<ImGuiMenuRenderer*>& queue);
#endif
    };
}
