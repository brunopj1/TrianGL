﻿#pragma once

#include <Core/Internal/Concepts/SmartPointerConcepts.h>
#include <Core/Services/Private/EntityManager.h>
#include <Game/Component.h>
#include <Game/Entity.h>

namespace TGL
{
	template <LazyPointerValue T>
	class LazyPtr
	{
	private:
		template <LazyPointerValue U>
		friend class LazyPtr;

	private:
		u64 m_Id;

	public:
		LazyPtr(T* ptr)
			: m_Id(ptr ? ptr->GetId() : 0) {}

		LazyPtr()
			: m_Id(0) {}

		~LazyPtr() = default;

	private:
		LazyPtr(const u64 id)
			: m_Id(id) {}

	public:
		LazyPtr(const LazyPtr& other)
			: m_Id(other.m_Id) {}

		LazyPtr(LazyPtr&& other) noexcept
			: m_Id(other.m_Id)
		{
			other.m_Id = 0;
		}

		LazyPtr& operator=(const LazyPtr& other)
		{
			if (this != &other)
			{
				m_Id = other.m_Id;
			}

			return *this;
		}

		LazyPtr& operator=(LazyPtr&& other) noexcept
		{
			if (this != &other)
			{
				m_Id = other.m_Id;
				other.m_Id = 0;
			}

			return *this;
		}

		LazyPtr& operator=(const T* ptr)
		{
			m_Id = ptr != nullptr ? ptr->GetId() : 0;
			return *this;
		}

	public:
		template <typename U>
			requires SmartPointerConversion<T, U>
		operator LazyPtr<U>() const // NOLINT(CppNonExplicitConversionOperator)
		{
			return LazyPtr<U>(m_Id);
		}

	public:
		friend bool operator==(const LazyPtr& left, const LazyPtr& right)
		{
			return left.m_Id == right.m_Id;
		}

		friend bool operator!=(const LazyPtr& left, const LazyPtr& right)
		{
			return left.m_Id != right.m_Id;
		}

		template <typename U>
			requires SmartPointerComparison<T, U>
		friend bool operator==(const LazyPtr& left, const LazyPtr<U>& right)
		{
			return left.m_Id == right.m_Id;
		}

		template <typename U>
			requires SmartPointerComparison<T, U>
		friend bool operator!=(const LazyPtr& left, const LazyPtr<U>& right)
		{
			return left.m_Id != right.m_Id;
		}

		friend bool operator==(const LazyPtr& left, std::nullptr_t)
		{
			return left.m_Id == 0;
		}

		friend bool operator!=(const LazyPtr& left, std::nullptr_t)
		{
			return left.m_Id != 0;
		}

	public:
		T* operator->()
		{
			return Get();
		}

		const T* operator->() const
		{
			return Get();
		}

		T* operator*()
		{
			return Get();
		}

		const T* operator*() const
		{
			return Get();
		}

	public:
		T* Get()
		{
			if (m_Id == 0)
			{
				return nullptr;
			}

			if constexpr (std::is_base_of_v<Entity, T>)
			{
				const EntityManager& entityManager = EntityManager::Get();
				Entity* entityPtr = entityManager.GetEntity(m_Id);
				T* ptr = entityPtr ? CastTo<T>(entityPtr) : nullptr;
				if (ptr == nullptr)
				{
					m_Id = 0;
				}
				return ptr;
			}
			else if constexpr (std::is_base_of_v<Component, T>)
			{
				const EntityManager& entityManager = EntityManager::Get();
				Component* componentPtr = entityManager.GetComponent(m_Id);
				T* ptr = componentPtr ? CastTo<T>(componentPtr) : nullptr;
				if (ptr == nullptr)
				{
					m_Id = 0;
				}
				return ptr;
			}
			else
			{
				m_Id = 0;
				return nullptr;
			}
		}

		const T* Get() const
		{
			if (m_Id == 0)
			{
				return nullptr;
			}

			if constexpr (std::is_base_of_v<Entity, T>)
			{
				const EntityManager& entityManager = EntityManager::Get();
				Entity* entityPtr = entityManager.GetEntity(m_Id);
				const T* ptr = entityPtr ? CastTo<T>(entityPtr) : nullptr;
				return ptr;
			}
			else if constexpr (std::is_base_of_v<Component, T>)
			{
				const EntityManager& entityManager = EntityManager::Get();
				Component* componentPtr = entityManager.GetComponent(m_Id);
				const T* ptr = componentPtr ? CastTo<T>(componentPtr) : nullptr;
				return ptr;
			}
			else
			{
				return nullptr;
			}
		}

		bool IsValid() const
		{
			return Get() != nullptr;
		}
	};

	template <LazyPointerValue To, LazyPointerValue From>
	LazyPtr<To> CastTo(const LazyPtr<From>& object)
	{
		if (object == nullptr)
		{
			return nullptr;
		}

		if constexpr (std::is_base_of_v<To, From>)
		{
			From* ptr = const_cast<From*>(object.Get());
			return LazyPtr(static_cast<To*>(ptr));
		}
		else if constexpr (std::is_base_of_v<From, To>)
		{
			From* ptr = const_cast<From*>(object.Get());
			return LazyPtr(dynamic_cast<To*>(ptr));
		}
		else
		{
			return nullptr;
		}
	}
}
