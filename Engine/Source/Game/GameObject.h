﻿#pragma once

#include <Core/Services/Internal/EntityManager.h>
#include <Internal/Concepts/EntitySystemConcepts.h>

namespace TGL
{
	class GameObject
	{
	private:
		friend class EntityManager;

		template <LazyPointerValue T>
		friend class LazyPtr;

	private:
		u64 m_Id = 0;
		bool m_ShouldUpdate;

	protected:
		GameObject(bool shouldUpdate);
		virtual ~GameObject() = default;

	protected:
		virtual i32 GetOrderOfExecution() const;

	protected:
		virtual void OnStart();
		virtual void OnUpdate(f32 deltaTime);

	public:
		template <typename T, typename... Args>
			requires SpawnableEntity<T, Args...>
		static T* SpawnEntity(Args&&... args);

	public:
		template <SearchableEntity T>
		static T* FindEntityGlobally();

		template <SearchableEntity T>
		static std::vector<T*> FindEntitiesGlobally();


		template <SearchableComponent T>
		static T* FindComponentGlobally();

		template <SearchableComponent T>
		static std::vector<T*> FindComponentsGlobally();
	};

	template <CastableGameObject To, CastableGameObject From>
	To* CastTo(From* object);

	// Template definitions

	template <typename T, typename... Args>
		requires SpawnableEntity<T, Args...>
	T* GameObject::SpawnEntity(Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
	{
		EntityManager& entityManager = EntityManager::Get();
		return entityManager.CreateEntity<T>(std::forward<Args>(args)...);
	}

	template <SearchableEntity T>
	T* GameObject::FindEntityGlobally()
	{
		EntityManager& entityManager = EntityManager::Get();
		return entityManager.FindEntityGlobally<T>();
	}

	template <SearchableEntity T>
	std::vector<T*> GameObject::FindEntitiesGlobally()
	{
		EntityManager& entityManager = EntityManager::Get();
		return entityManager.FindEntitiesGlobally<T>();
	}

	template <SearchableComponent T>
	T* GameObject::FindComponentGlobally()
	{
		EntityManager& entityManager = EntityManager::Get();
		return entityManager.FindComponentGlobally<T>();
	}

	template <SearchableComponent T>
	std::vector<T*> GameObject::FindComponentsGlobally()
	{
		EntityManager& entityManager = EntityManager::Get();
		return entityManager.FindComponentsGlobally<T>();
	}

	template <CastableGameObject To, CastableGameObject From>
	To* CastTo(From* object)
	{
		if (object == nullptr)
		{
			return nullptr;
		}

		if constexpr (std::is_base_of_v<To, From>)
		{
			return static_cast<To*>(object);
		}
		else if constexpr (std::is_base_of_v<From, To>)
		{
			return dynamic_cast<To*>(object);
		}
		else
		{
			return nullptr;
		}
	}
}
