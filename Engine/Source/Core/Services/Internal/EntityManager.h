#pragma once

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
	class EntityManager final : public Service<EntityManager>
	{
	private:
		friend class Application;
		friend class RenderLayer;
		friend class GameObject;
		friend class GameMode;
		friend class Entity;
		friend class Component;
		friend class Renderable;

		template <LazyPointerValue T>
		friend class LazyPtr;

	private:
		DECLARE_SPAWNER_ASSERT_VAR(GameMode);
		DECLARE_SPAWNER_ASSERT_VAR(Entity);
		DECLARE_SPAWNER_ASSERT_VAR(Component);

	private:
		u64 m_NextId;

	private:
		GameMode* m_GameMode = nullptr;

		std::unordered_map<u64, Entity*> m_Entities;
		std::unordered_map<u64, Component*> m_Components;

		std::vector<GameObject*> m_OnUpdateQueue;
		std::vector<GameObject*> m_OnStartQueue;

		std::vector<Renderable*> m_RenderQueue;

	private:
		EntityManager() = default;
		~EntityManager() = default;

	private:
		void Init();
		void Terminate();

	private:
		void Update(f32 deltaTime);
		void Render() const;

	private:
		GameMode* GetGameMode() const;
		Entity* GetEntity(u64 id) const;
		Component* GetComponent(u64 id) const;

		u32 GetEntityCount() const;
		u32 GetComponentCount() const;

	private:
		void StoreObjectCallbacks(GameObject* object);
		void RemoveObjectCallbacks(GameObject* object);

	private:
		static void AddToUpdateQueue(GameObject* object, std::vector<GameObject*>& queue);
		static void AddToRenderQueue(Renderable* renderable, std::vector<Renderable*>& queue);

	private:
		void UpdateRenderableOrder(Renderable* renderable);

	private:
		// This cannot be executed directly because of circular dependencies
		static void SetupEntityComponentRelationship(Entity* entity, Component* component);

	private:
		template <typename T, typename... Args>
			requires SpawnableGameMode<T, Args...>
		T* CreateGameMode(Args&&... args);

		void DestroyGameMode();

		template <typename T, typename... Args>
			requires SpawnableEntity<T, Args...>
		T* CreateEntity(Args&&... args);

		void DestroyEntity(Entity* entity);

		template <typename T, typename... Args>
			requires SpawnableComponent<T, Args...>
		T* CreateComponent(Entity* parent, Args&&... args);

		void DestroyComponent(Component* component);

	private:
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

	template <typename T, typename... Args>
		requires SpawnableGameMode<T, Args...>
	T* EntityManager::CreateGameMode(Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
	{
		PREPARE_SPAWNER_ASSERT(GameMode);

		T* instance = new T(std::forward<Args>(args)...);

		instance->m_Id = m_NextId++;

		m_GameMode = instance;

		StoreObjectCallbacks(instance);

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
		for (auto entity : m_Entities)
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

		for (auto component : m_Components)
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
