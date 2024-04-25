#pragma once

#include "Util/Macros/SmartPointerMacros.h"
#include "Core/EntityManager.h"
#include "Game/Entity.h"
#include "Game/Component.h"

// TODO remove the get and is valid methods and overload the relevant operators
// TODO add the copy / move / assignment operators for convertible types
// TODO add the comparison operators for convertible types

namespace TGL
{
    template <typename T, typename = LAZY_POINTER_TEMPLATE_CONDITION>
    class LazyPtr
    {
    private:
        uint64_t m_Id;

    public:
        LazyPtr(T* value)
            : m_Id(value ? value->m_Id : 0)
        {}

        LazyPtr()
            : m_Id(0)
        {}

        ~LazyPtr() = default;

    public:
        LazyPtr(const LazyPtr& other)
            : m_Id(other.m_Id)
        {}

        LazyPtr(LazyPtr&& other) noexcept
            : m_Id(other.m_Id)
        {}

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
            }
            
            return *this;
        }

        LazyPtr& operator=(const T* value)
        {
            m_Id = value != nullptr ? value->m_Id : 0;
            return *this;
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
            return left.m_Id >= 0; // NOLINT
        }

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

        bool IsValid() const
        {
            return Get() != nullptr;
        }
    };
}
