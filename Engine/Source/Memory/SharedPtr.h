﻿#pragma once

#include "Core/Internal/Concepts/SmartPointerConcepts.h"
#include "Core/Internal/Macros/AssetFactoryMacros.h"
#include "Core/Internal/Macros/ClassMacros.h"
#include <Core/DataTypes.h>
#include <cstddef>
#include <type_traits>

// TODO control access by using SharedPtr<const T> instead of const SharedPtr<T>

namespace TGL
{
	// Forward declarations
	template <typename U>
	class SharedFromThis;

	class ReferenceCounter final
	{
	private:
		template <typename T>
		friend class SharedPtr;

	private:
		u32 m_Counter = 1;
	};

	class AssetFactoryUtil final
	{
	private:
		friend class AssetManager;

		template <typename T>
		friend class SharedPtr;

		friend class Animation;
		friend class AnimationFrame;
		friend class AnimationSprite;
		friend class Audio;
		friend class Material;
		friend class MaterialUniform;
		friend class Texture;
		friend class TextureSlice;

	private:
		DECLARE_ASSET_FACTORY_DESTRUCTOR_VAR();

	public:
		AssetFactoryUtil() = delete;
		~AssetFactoryUtil() = delete;

	public:
		DELETE_COPY_AND_MOVE_CONSTRUCTORS(AssetFactoryUtil);
	};

	// TODO use the 'SharedPointerValue' concept here
	template <typename T>
	class SharedPtr final
	{
	private:
		friend class AssetManager;

		template <typename U>
		friend class SharedPtr;

		template <typename U>
		friend class SharedFromThis;

		template <typename To, typename From>
		friend SharedPtr<To> CastTo(const SharedPtr<From>& object);

	private:
		T* m_Pointer;
		ReferenceCounter* m_ReferenceCounter;

	public:
		SharedPtr()
			: m_Pointer(nullptr), m_ReferenceCounter(nullptr) {}

		SharedPtr(std::nullptr_t)
			: m_Pointer(nullptr), m_ReferenceCounter(nullptr) {}

	private:
		SharedPtr(T* ptr)
			: m_Pointer(ptr), m_ReferenceCounter(ptr != nullptr ? new ReferenceCounter() : nullptr)
		{
			if constexpr (std::is_base_of_v<SharedFromThis<T>, T>)
			{
				if (ptr != nullptr)
				{
					ptr->m_Pointer = ptr;
					ptr->m_ReferenceCounter = m_ReferenceCounter;
				}
			}
		}

		SharedPtr(T* ptr, ReferenceCounter* referenceCounter)
			: m_Pointer(ptr), m_ReferenceCounter(referenceCounter)
		{
			Increment();
		}

	public:
		~SharedPtr()
		{
			Decrement();
		}

	public:
		SharedPtr(const SharedPtr& other)
			: m_Pointer(other.m_Pointer), m_ReferenceCounter(other.m_ReferenceCounter)
		{
			Increment();
		}

		SharedPtr(SharedPtr&& other) noexcept
			: m_Pointer(other.m_Pointer), m_ReferenceCounter(other.m_ReferenceCounter)
		{
			other.m_Pointer = nullptr;
			other.m_ReferenceCounter = nullptr;
		}

		SharedPtr& operator=(const SharedPtr& other) // NOLINT(bugprone-unhandled-self-assignment)
		{
			if (this != &other)
			{
				Decrement();
				m_Pointer = other.m_Pointer;
				m_ReferenceCounter = other.m_ReferenceCounter;
				Increment();
			}

			return *this;
		}

		SharedPtr& operator=(SharedPtr&& other) noexcept
		{
			if (this != &other)
			{
				Decrement();
				m_Pointer = other.m_Pointer;
				m_ReferenceCounter = other.m_ReferenceCounter;
				other.m_Pointer = nullptr;
				other.m_ReferenceCounter = nullptr;
			}

			return *this;
		}

		SharedPtr& operator=(std::nullptr_t)
		{
			Decrement();
			m_Pointer = nullptr;
			m_ReferenceCounter = nullptr;
			return *this;
		}

		template <typename U>
			requires SmartPointerConversion<T, U>
		operator SharedPtr<U>() const // NOLINT(CppNonExplicitConversionOperator)
		{
			return SharedPtr<U>(m_Pointer, m_ReferenceCounter);
		}

	public:
		friend bool operator==(const SharedPtr& left, const SharedPtr& right)
		{
			return left.m_ReferenceCounter == right.m_ReferenceCounter;
		}

		friend bool operator!=(const SharedPtr& left, const SharedPtr& right)
		{
			return left.m_ReferenceCounter != right.m_ReferenceCounter;
		}

		template <typename U>
			requires SmartPointerComparison<T, U>
		friend bool operator==(const SharedPtr& left, const SharedPtr<U>& right)
		{
			return left.Get() == right.Get();
		}

		template <typename U>
			requires SmartPointerComparison<T, U>
		friend bool operator!=(const SharedPtr& left, const SharedPtr<U>& right)
		{
			return left.Get() != right.Get();
		}

		friend bool operator==(const SharedPtr& left, std::nullptr_t)
		{
			return left.Get() == nullptr;
		}

		friend bool operator!=(const SharedPtr& left, std::nullptr_t)
		{
			return left.Get() != nullptr;
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
			return m_Pointer;
		}

		const T* Get() const
		{
			return m_Pointer;
		}

		bool IsValid() const
		{
			return Get() != nullptr;
		}

	private:
		void Increment() const
		{
			if (m_ReferenceCounter == nullptr)
			{
				return;
			}

			m_ReferenceCounter->m_Counter++;
		}

		void Decrement() const
		{
			if (m_ReferenceCounter == nullptr)
			{
				return;
			}

			m_ReferenceCounter->m_Counter--;

			if (m_ReferenceCounter->m_Counter == 0)
			{
				PREPARE_ASSET_FACTORY_DESTRUCTOR();

				delete m_ReferenceCounter;
				delete m_Pointer;

				ASSERT_POST_ASSET_FACTORY_DESTRUCTOR();
			}
		}
	};

	template <typename T>
	class SharedFromThis
	{
	private:
		friend class AssetManager;

		template <typename U>
		friend class SharedPtr;

	private:
		T* m_Pointer = nullptr;
		ReferenceCounter* m_ReferenceCounter = nullptr;

	protected:
		SharedPtr<T> ToSharedPtr() const
		{
			return SharedPtr<T>(m_Pointer, m_ReferenceCounter);
		}
	};

	template <typename To, typename From>
	SharedPtr<To> CastTo(const SharedPtr<From>& object)
	{
		if (object == nullptr)
		{
			return nullptr;
		}

		if constexpr (std::is_base_of_v<To, From>)
		{
			From* ptr = const_cast<From*>(object.Get());
			return SharedPtr<To>(static_cast<To*>(ptr), object.m_ReferenceCounter);
		}
		else if constexpr (std::is_base_of_v<From, To>)
		{
			From* ptr = const_cast<From*>(object.Get());
			return SharedPtr<To>(dynamic_cast<To*>(ptr), object.m_ReferenceCounter);
		}
		else
		{
			return nullptr;
		}
	}
}
