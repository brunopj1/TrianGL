#pragma once

#include "Exceptions/Game/GameModeAlreadySpecifiedException.hpp"
#include <vector>
#include <unordered_map>

#include "Util/Macros/SingletonMacros.hpp"
#include "Util/Macros/SpawnerMacros.hpp"
#include <ranges>

#ifdef DEBUG
#include "Game/ImGui/ImGuiMenuRender.h"
#endif

namespace TGL
{
    // Forward declarations
    class Object;
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
        friend class Object;
        friend class GameMode;
        friend class Entity;
        friend class Component;

        template <typename T, typename C>
        friend class LazyPtr;

    private:
        DECLARE_SINGLETON_INSTANCE_VAR(TGL::EntityManager);

    private:
        DECLARE_SPAWNER_USAGE_VAR(GameMode);
        DECLARE_SPAWNER_USAGE_VAR(Entity);
        DECLARE_SPAWNER_USAGE_VAR(Component);

    private:
        uint64_t m_NextId = 1;

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
        EntityManager();
        ~EntityManager();

    private:
        void Terminate() const;

    private:
        void Update(float deltaTime);
        void Render() const;

    private:
        static GameMode* GetGameMode();
        static Entity* GetEntity(uint64_t id);
        static Component* GetComponent(uint64_t id);

        static size_t GetEntityCount();
        static size_t GetComponentCount();

    private:
        static void AddToQueue(Updatable* updatable, std::vector<Updatable*>& queue);

#ifdef DEBUG
        static void AddToImGuiQueue(ImGuiMenuRenderer* renderer, std::vector<ImGuiMenuRenderer*>& queue);
#endif

    private:
        void StoreObjectCallbacks(Object* object);
        void RemoveObjectCallbacks(Object* object);

    private:
        // This cannot be executed directly because of circular dependencies
        static void SetupEntityComponentRelationship(Entity* entity, Component* component);

    private:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::GameMode)>
        static void CreateGameMode(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            ASSERT_SINGLETON_INITIALIZED();

            if (s_Instance->m_GameMode != nullptr) throw GameModeAlreadySpecifiedException();

            PREPARE_SPAWNER_USAGE(GameMode);

            T* instance = new T(std::forward<Args>(args)...);

            instance->m_Id = s_Instance->m_NextId++;

            s_Instance->m_GameMode = instance;

            s_Instance->StoreObjectCallbacks(instance);
        }

        static void DestroyGameMode();

        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::Entity)>
        static T* CreateEntity(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            ASSERT_SINGLETON_INITIALIZED();

            PREPARE_SPAWNER_USAGE(Entity);

            T* instance = new T(std::forward<Args>(args)...);

            instance->m_Id = s_Instance->m_NextId++;

            s_Instance->m_Entities.emplace(instance->m_Id, instance);

            AddToQueue(instance, s_Instance->m_OnStartQueue);
            AddToQueue(instance, s_Instance->m_OnUpdateQueue);

            s_Instance->StoreObjectCallbacks(instance);

            return instance;
        }

        static void DestroyEntity(Entity* entity);

        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::Component)>
        static T* CreateComponent(Entity* parent, Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            ASSERT_SINGLETON_INITIALIZED();

            PREPARE_SPAWNER_USAGE(Component);

            T* instance = new T(std::forward<Args>(args)...);

            instance->m_Id = s_Instance->m_NextId++;

            s_Instance->m_Components.emplace(instance->m_Id, instance);

            AddToQueue(instance, s_Instance->m_OnStartQueue);
            AddToQueue(instance, s_Instance->m_OnUpdateQueue);

            s_Instance->StoreObjectCallbacks(instance);

            SetupEntityComponentRelationship(parent, instance);

            return instance;
        }

        static void DestroyComponent(Component* component);

    private:
        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(TGL::Entity)>
        static T* FindEntityGlobally()
        {
            ASSERT_SINGLETON_INITIALIZED();

            for (auto entity : s_Instance->m_Entities)
            {
                if (T* casted = dynamic_cast<T*>(entity))
                {
                    return casted;
                }
            }

            return nullptr;
        }

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(TGL::Entity)>
        static std::vector<T*> FindEntitiesGlobally()
        {
            ASSERT_SINGLETON_INITIALIZED();

            std::vector<T*> entities;

            for (auto entity : s_Instance->m_Entities | std::views::values)
            {
                if (T* casted = dynamic_cast<T*>(entity))
                {
                    entities.push_back(casted);
                }
            }

            return entities;
        }

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(TGL::Component)>
        static T* FindComponentGlobally()
        {
            ASSERT_SINGLETON_INITIALIZED();

            for (auto component : s_Instance->m_Components | std::views::values)
            {
                if (T* casted = dynamic_cast<T*>(component))
                {
                    return casted;
                }
            }

            return nullptr;
        }

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(TGL::Component)>
        static std::vector<T*> FindComponentsGlobally()
        {
            ASSERT_SINGLETON_INITIALIZED();

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

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(TGL::Component)>
        T* FindComponentInEntity(const std::vector<Component*>& entityComponents)
        {
            ASSERT_SINGLETON_INITIALIZED();

            for (auto component : entityComponents)
            {
                if (T* casted = dynamic_cast<T*>(component))
                {
                    return casted;
                }
            }

            return nullptr;
        }

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(TGL::Component)>
        std::vector<T*> FindComponentsInEntity(const std::vector<Component*>& entityComponents)
        {
            ASSERT_SINGLETON_INITIALIZED();

            std::vector<T*> components;

            for (auto component : entityComponents)
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
