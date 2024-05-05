#pragma once

#include "Util/Concepts/SmartPointerConcepts.h"
#include "Core/EntityManager.h"
#include "Game/Entity.h"
#include "Game/Component.h"

namespace TGL
{
    template <LazyPointerValue T>
    class LazyPtr
    {
    private:
        template <LazyPointerValue U>
        friend class LazyPtr;

    private:
        uint64_t m_Id;

    public:
        LazyPtr(T* ptr)
            : m_Id(ptr ? ptr->m_Id : 0)
        {}

        LazyPtr()
            : m_Id(0)
        {}

        ~LazyPtr() = default;

    private:
        LazyPtr(const uint64_t id)
            : m_Id(id)
        {}

    public:
        LazyPtr(const LazyPtr& other)
            : m_Id(other.m_Id)
        {}

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
            m_Id = ptr != nullptr ? ptr->m_Id : 0;
            return *this;
        }

    public:
        template <typename U, typename = std::enable_if_t<std::is_base_of_v<U, T>>>
        operator LazyPtr<U>() const // NOLINT(CppNonExplicitConversionOperator)
        {
            return LazyPtr<U>(m_Id);
        }

        template <typename U>
        LazyPtr<U> CastTo()
        {
            T* ptr = Get();

            if (ptr == nullptr) return nullptr;

            U* casted = dynamic_cast<U*>(ptr);

            if (casted != nullptr)
            {
                return LazyPtr<U>(casted);
            }

            return nullptr;
        }

    public:
        friend bool operator==(const LazyPtr& left, const LazyPtr& right)
        {
            return left.m_Id == right.m_Id;
        }

        friend bool operator==(const LazyPtr& left, std::nullptr_t)
        {
            return left.m_Id == 0;
        }

        friend bool operator!=(const LazyPtr& left, const LazyPtr& right)
        {
            return left.m_Id != right.m_Id;
        }

        friend bool operator!=(const LazyPtr& left, std::nullptr_t)
        {
            return left.m_Id != 0;
        }

        friend bool operator<(const LazyPtr& left, const LazyPtr& right)
        {
            return left.m_Id < right.m_Id;
        }

        friend bool operator<(const LazyPtr& left, std::nullptr_t)
        {
            return left.m_Id < 0;
        }

        friend bool operator<=(const LazyPtr& left, const LazyPtr& right)
        {
            return left.m_Id <= right.m_Id;
        }

        friend bool operator<=(const LazyPtr& left, std::nullptr_t)
        {
            return left.m_Id <= 0;
        }

        friend bool operator>(const LazyPtr& left, const LazyPtr& right)
        {
            return left.m_Id > right.m_Id;
        }

        friend bool operator>(const LazyPtr& left, std::nullptr_t)
        {
            return left.m_Id > 0;
        }

        friend bool operator>=(const LazyPtr& left, const LazyPtr& right)
        {
            return left.m_Id >= right.m_Id;
        }

        friend bool operator>=(const LazyPtr& left, std::nullptr_t)
        {
            return left.m_Id >= 0; // NOLINT(CppUnsignedZeroComparison)
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
        T* Get()
        {
            if (m_Id == 0) return nullptr;

            if constexpr (std::is_base_of_v<Entity, T>)
            {
                Entity* entityPtr = EntityManager::GetEntity(m_Id);
                T* ptr = entityPtr ? entityPtr->CastTo<T>() : nullptr;
                if (ptr == nullptr) m_Id = 0;
                return ptr;
            }
            else if constexpr (std::is_base_of_v<Component, T>)
            {
                Component* componentPtr = EntityManager::GetComponent(m_Id);
                T* ptr = componentPtr ? componentPtr->CastTo<T>() : nullptr;
                if (ptr == nullptr) m_Id = 0;
                return ptr;
            }
            else
            {
                m_Id = 0;
                return nullptr;
            }
        }

        T* Get() const
        {
            if (m_Id == 0) return nullptr;

            if constexpr (std::is_base_of_v<Entity, T>)
            {
                Entity* entityPtr = EntityManager::GetEntity(m_Id);
                T* ptr = entityPtr ? entityPtr->CastTo<T>() : nullptr;
                return ptr;
            }
            else if constexpr (std::is_base_of_v<Component, T>)
            {
                Component* componentPtr = EntityManager::GetComponent(m_Id);
                T* ptr = componentPtr ? componentPtr->CastTo<T>() : nullptr;
                return ptr;
            }
            else
            {
                return nullptr;
            }
        }

        bool IsValid()
        {
            return Get() != nullptr;
        }

        bool IsValid() const
        {
            return Get() != nullptr;
        }
    };
}
