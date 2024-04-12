﻿#pragma once

#include "Exceptions/Game/GameModeAlreadySpecifiedException.h"
#include <vector>
#include <unordered_map>

#include "Util/Macros/SingletonMacros.h"
#include "Util/Macros/SpawnerMacros.h"
#include <ranges>

namespace TGL
{
    class EntityManager final
    {
    private:
        friend class Application;
        friend class GameObject;
        friend class GameMode;
        friend class Entity;
        friend class Component;
        friend class Renderable;

        template <typename T, typename Condition>
        friend class LazyPtr;

    private:
        DECLARE_SPAWNER_USAGE_VAR(GameMode);
        DECLARE_SPAWNER_USAGE_VAR(Entity);
        DECLARE_SPAWNER_USAGE_VAR(Component);

    private:
        static inline bool s_CanCreateAndDestroyObjects = false;

    private:
        static inline uint64_t s_NextId = 1;

    private:
        static inline GameMode* s_GameMode = nullptr;

        static inline std::unordered_map<uint64_t, Entity*> s_Entities;
        static inline std::unordered_map<uint64_t, Component*> s_Components;

        static inline std::vector<GameObject*> s_OnUpdateQueue;
        static inline std::vector<GameObject*> s_OnStartQueue;

        static inline std::vector<Renderable*> s_RenderQueue;

    public:
        EntityManager() = delete;
        ~EntityManager() = delete;

    private:
        static void Init();
        static void Terminate();

    private:
        static void Update(float deltaTime);
        static void Render();

    private:
        static GameMode* GetGameMode();
        static Entity* GetEntity(uint64_t id);
        static Component* GetComponent(uint64_t id);

        static size_t GetEntityCount();
        static size_t GetComponentCount();

    private:
        static void AddToUpdateQueue(GameObject* object, std::vector<GameObject*>& queue);
        static void AddToRenderQueue(Renderable* renderable, std::vector<Renderable*>& queue);

    private:
        static void StoreObjectCallbacks(GameObject* object);
        static void RemoveObjectCallbacks(GameObject* object);

    private:
        static void UpdateRenderableOrder(Renderable* renderable);

    private:
        // This cannot be executed directly because of circular dependencies
        static void SetupEntityComponentRelationship(Entity* entity, Component* component);

    private:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::GameMode)>
        static void CreateGameMode(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            ASSERT_SINGLETON_OBJECT_CREATION_NO_RET();

            if (s_GameMode != nullptr) throw GameModeAlreadySpecifiedException();

            PREPARE_SPAWNER_USAGE(GameMode);

            T* instance = new T(std::forward<Args>(args)...);

            instance->m_Id = s_NextId++;

            s_GameMode = instance;

            StoreObjectCallbacks(instance);
        }

        static void DestroyGameMode();

        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::Entity)>
        static T* CreateEntity(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            ASSERT_SINGLETON_OBJECT_CREATION();

            PREPARE_SPAWNER_USAGE(Entity);

            T* instance = new T(std::forward<Args>(args)...);

            instance->m_Id = s_NextId++;

            s_Entities.emplace(instance->m_Id, instance);

            StoreObjectCallbacks(instance);

            return instance;
        }

        static void DestroyEntity(Entity* entity);

        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::Component)>
        static T* CreateComponent(Entity* parent, Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            ASSERT_SINGLETON_OBJECT_CREATION();

            PREPARE_SPAWNER_USAGE(Component);

            T* instance = new T(std::forward<Args>(args)...);

            instance->m_Id = s_NextId++;

            s_Components.emplace(instance->m_Id, instance);

            StoreObjectCallbacks(instance);

            SetupEntityComponentRelationship(parent, instance);

            return instance;
        }

        static void DestroyComponent(Component* component);

    private:
        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(TGL::Entity)>
        static T* FindEntityGlobally()
        {
            for (auto entity : s_Entities)
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
            std::vector<T*> entities;

            for (auto entity : s_Entities | std::views::values)
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
            for (auto component : s_Components | std::views::values)
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
            std::vector<T*> components;

            for (auto component : s_Components)
            {
                if (T* casted = dynamic_cast<T*>(component))
                {
                    components.push_back(casted);
                }
            }

            return components;
        }

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(TGL::Component)>
        static T* FindComponentInEntity(const std::vector<Component*>& entityComponents)
        {
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
        static std::vector<T*> FindComponentsInEntity(const std::vector<Component*>& entityComponents)
        {
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
