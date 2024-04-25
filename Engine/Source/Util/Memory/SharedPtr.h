#pragma once

#include "Util/Macros/SmartPointerMacros.h"

// TODO only allow destruction from inside the reference counter (SPAWNER MACROS)

namespace TGL
{
	class ReferenceCounter final
	{
	private:
		template <typename T>
		friend class SharedPtr;

	private:
		unsigned int m_Counter = 1;
	};

	template <typename T>
	class SharedPtr final
	{
	private:
		friend class AssetManager;

		template <typename U>
		friend class SharedPtr;

		template <typename U>
		friend class SharedFromThis;

	private:
		T* m_Pointer;
		ReferenceCounter* m_ReferenceCounter;

	public:
		SharedPtr()
			: m_Pointer(nullptr), m_ReferenceCounter(nullptr)
		{}

		SharedPtr(std::nullptr_t)
			: m_Pointer(nullptr), m_ReferenceCounter(nullptr)
		{}

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

		SharedPtr& operator=(const SharedPtr& other) // NOLINT
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
		operator SharedPtr<U>() const // NOLINT
		{
			static_assert(std::is_base_of_v<U, T>, "Cannot convert T to the unrelated type U");
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

		friend bool operator==(const SharedPtr& left, std::nullptr_t)
		{
			return left.Get() == nullptr;
		}

		friend bool operator!=(const SharedPtr& left, std::nullptr_t)
		{
			return left.Get() != nullptr;
		}

	public:
		T* operator->() const
		{
			return Get();
		}

		T* operator*() const
		{
			return Get();
		}

	public:
		T* Get() const
		{
			return m_Pointer;
		}

		bool IsValid() const
		{
			return Get() != nullptr;
		}

		template <typename U>
		SharedPtr<U> CastTo()
		{
			U* casted = dynamic_cast<U*>(m_Pointer);

			if (casted != nullptr)
			{
				return SharedPtr<U>(casted, m_ReferenceCounter);
			}

			return nullptr;
		}

	private:
		void Increment() const
		{
			if (m_ReferenceCounter == nullptr) return;

			m_ReferenceCounter->m_Counter++;
		}

		void Decrement() const
		{
			if (m_ReferenceCounter == nullptr) return;

			m_ReferenceCounter->m_Counter--;

			if (m_ReferenceCounter->m_Counter == 0)
			{
				delete m_ReferenceCounter;
				delete m_Pointer;
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
		SharedPtr<T> ToSharedPtr()
		{
			return SharedPtr<T>(m_Pointer, m_ReferenceCounter);
		}
	};
}