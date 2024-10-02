#pragma once

#include "Internal/Macros/TestMacros.h"
#include <Core/DataTypes.h>
#include <Core/Service.h>
#include <Internal/Asserts/SpawnerAsserts.h>
#include <Internal/Concepts/EntitySystemConcepts.h>
#include <Internal/Concepts/SmartPointerConcepts.h>
#include <ranges>
#include <unordered_map>
#include <vector>

namespace TGL
{
	class EntityManager : public Service<EntityManager>
	{
	private:
		friend class Application;
		friend class ServiceCollection;
		friend struct ServiceDeleter<EntityManager>;

		friend class RenderBackend;
		friend class GameObject;
		friend class GameMode;
		friend class Entity;
		friend class Component;
		friend class Renderable;

		template <LazyPointerValue T>
		friend class LazyPtr;

	private:
		DECLARE_SPAWNER_EXPECT_VAR(GameMode);
		DECLARE_SPAWNER_EXPECT_VAR(Entity);
		DECLARE_SPAWNER_EXPECT_VAR(Component);

	protected:
		u64 m_NextId;

	protected:
		GameMode* m_GameMode = nullptr;

		std::unordered_map<u64, Entity*> m_Entities;
		std::unordered_map<u64, Component*> m_Components;

		std::vector<GameObject*> m_OnUpdateQueue;
		std::vector<GameObject*> m_OnStartQueue;

		std::vector<Renderable*> m_RenderQueue;

	protected:
		EntityManager() = default;
		MOCKABLE_DESTRUCTOR ~EntityManager() = default;

	protected:
		MOCKABLE_METHOD void Init();
		MOCKABLE_METHOD void Terminate();

	protected:
		MOCKABLE_METHOD void Update(f32 deltaTime);
		MOCKABLE_METHOD void Render() const;

	protected:
		MOCKABLE_METHOD GameMode* GetGameMode() const;
		MOCKABLE_METHOD Entity* GetEntity(u64 id) const;
		MOCKABLE_METHOD Component* GetComponent(u64 id) const;

		MOCKABLE_METHOD u32 GetEntityCount() const;
		MOCKABLE_METHOD u32 GetComponentCount() const;

	protected:
		template <typename T>
		void StoreObjectCallbacks(T* object);
		void RemoveObjectCallbacks(GameObject* object);

	protected:
		MOCKABLE_METHOD void AddToUpdateQueue(GameObject* object, std::vector<GameObject*>& queue);
		MOCKABLE_METHOD void AddToRenderQueue(Renderable* renderable, std::vector<Renderable*>& queue);

	protected:
		MOCKABLE_METHOD void UpdateRenderableOrder(Renderable* renderable);

	protected:
		// This cannot be executed directly because of circular dependencies
		MOCKABLE_METHOD void SetupEntityComponentRelationship(Entity* entity, Component* component);

	protected:
		template <typename T, typename... Args>
			requires SpawnableGameMode<T, Args...>
		T* CreateGameMode(Args&&... args);

		MOCKABLE_METHOD void DestroyGameMode();

		template <typename T, typename... Args>
			requires SpawnableEntity<T, Args...>
		T* CreateEntity(Args&&... args);

		MOCKABLE_METHOD void DestroyEntity(Entity* entity);

		template <typename T, typename... Args>
			requires SpawnableComponent<T, Args...>
		T* CreateComponent(Entity* parent, Args&&... args);

		MOCKABLE_METHOD void DestroyComponent(Component* component);

	protected:
		template <SearchableEntity T>
		T* FindEntityGlobally();

		template <SearchableEntity T>
		std::vector<T*> FindEntitiesGlobally();

		template <SearchableComponent T>
		T* FindComponentGlobally();

		template <SearchableComponent T>
		std::vector<T*> FindComponentsGlobally();

		template <SearchableComponent T>
		T* FindComponentInEntity(const std::vector<Component*>& entityComponents);

		template <SearchableComponent T>
		std::vector<T*> FindComponentsInEntity(const std::vector<Component*>& entityComponents);
	};

	// Template definitions

	template <typename T>
	void EntityManager::StoreObjectCallbacks(T* object)
	{
		// Updatable

		if constexpr (std::is_base_of_v<GameMode, T>)
		{
			// No need to add to the OnStartQueue because the GameMode::OnStart will be called manually
			AddToUpdateQueue(object, m_OnUpdateQueue);
		}
		else /* Entity or Component */
		{
			// No need to add to the OnUpdateQueue because it will be added automatically after leaving the OnStartQueue
			AddToUpdateQueue(object, m_OnStartQueue);
		}

		// Renderable

		if constexpr (std::is_base_of_v<Renderable, T>)
		{
			AddToRenderQueue(object, m_RenderQueue);
		}
	}

	template <typename T, typename... Args>
		requires SpawnableGameMode<T, Args...>
	T* EntityManager::CreateGameMode(Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
	{
		PREPARE_SPAWNER_ASSERT(GameMode);

		T* instance = new T(std::forward<Args>(args)...);

		instance->m_Id = m_NextId++;

		m_GameMode = instance;

		StoreObjectCallbacks(instance);

		// Remove from the start queue because the GameMode::OnStart will be called manually
		std::erase(m_OnStartQueue, instance);

		return instance;
	}

	template <typename T, typename... Args>
		requires SpawnableEntity<T, Args...>
	T* EntityManager::CreateEntity(Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
	{
		PREPARE_SPAWNER_ASSERT(Entity);

		T* instance = new T(std::forward<Args>(args)...);

		instance->m_Id = m_NextId++;

		m_Entities.emplace(instance->m_Id, instance);

		StoreObjectCallbacks(instance);

		return instance;
	}

	template <typename T, typename... Args>
		requires SpawnableComponent<T, Args...>
	T* EntityManager::CreateComponent(Entity* parent, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
	{
		PREPARE_SPAWNER_ASSERT(Component);

		T* instance = new T(std::forward<Args>(args)...);

		instance->m_Id = m_NextId++;

		m_Components.emplace(instance->m_Id, instance);

		StoreObjectCallbacks(instance);

		SetupEntityComponentRelationship(parent, instance);

		return instance;
	}

	template <SearchableEntity T>
	T* EntityManager::FindEntityGlobally()
	{
		for (auto entity : m_Entities | std::views::values)
		{
			if (T* casted = dynamic_cast<T*>(entity))
			{
				return casted;
			}
		}

		return nullptr;
	}

	template <SearchableEntity T>
	std::vector<T*> EntityManager::FindEntitiesGlobally()
	{
		std::vector<T*> entities;

		for (auto entity : m_Entities | std::views::values)
		{
			if (T* casted = dynamic_cast<T*>(entity))
			{
				entities.push_back(casted);
			}
		}

		return entities;
	}

	template <SearchableComponent T>
	T* EntityManager::FindComponentGlobally()
	{
		for (auto component : m_Components | std::views::values)
		{
			if (T* casted = dynamic_cast<T*>(component))
			{
				return casted;
			}
		}

		return nullptr;
	}

	template <SearchableComponent T>
	std::vector<T*> EntityManager::FindComponentsGlobally()
	{
		std::vector<T*> components;

		for (auto component : m_Components | std::views::values)
		{
			if (T* casted = dynamic_cast<T*>(component))
			{
				components.push_back(casted);
			}
		}

		return components;
	}

	template <SearchableComponent T>
	T* EntityManager::FindComponentInEntity(const std::vector<Component*>& entityComponents)
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

	template <SearchableComponent T>
	std::vector<T*> EntityManager::FindComponentsInEntity(const std::vector<Component*>& entityComponents)
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
}
