#pragma once

#include "Util/Macros/LazyPointerMacros.hpp"
#include "Core/EntityManager.h"
#include "Core/ResourceManager.h"
#include "Game/Entity.h"
#include "Game/Component.h"
#include "Resources/Base/Resource.h"


namespace TGL
{
    template <typename T, typename = LAZY_PONTER_TEMPLATE_CONDITION>
    class LazyPtr
    {
    private:
        uint64_t m_Id;

    public:
        LazyPtr(T* value)
        {
            m_Id = value ? value->m_Id : 0;
        }

        LazyPtr(std::nullptr_t)
        {
            m_Id = 0;
        }

        LazyPtr()
        {
            m_Id = 0;
        }

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
            if (this == &other) return *this;
            m_Id = other.m_Id;
            return *this;
        }

        LazyPtr& operator=(LazyPtr&& other) noexcept
        {
            if (this == &other) return *this;
            m_Id = other.m_Id;
            return *this;
        }

        LazyPtr& operator=(const T* value)
        {
            m_Id = value->m_Id;
            return *this;
        }

        LazyPtr& operator=(std::nullptr_t)
        {
            m_Id = 0;
            return *this;
        }

    public:
        T* Get()
        {
            if (m_Id == 0) return nullptr;

            if constexpr (std::is_base_of_v<Entity, T>)
            {
                Entity* entityPtr = EntityManager::GetEntity(m_Id);
                T* ptr = entityPtr ? entityPtr->As<T>() : nullptr;
                if (ptr == nullptr) m_Id = 0;
                return ptr;
            }
            else if constexpr (std::is_base_of_v<Component, T>)
            {
                Component* componentPtr = EntityManager::GetComponent(m_Id);
                T* ptr = componentPtr ? componentPtr->As<T>() : nullptr;
                if (ptr == nullptr) m_Id = 0;
                return ptr;
            }
            else if constexpr (std::is_base_of_v<Resource, T>)
            {
                Resource* resourcePtr = ResourceManager::GetResource(m_Id);
                T* ptr = resourcePtr ? resourcePtr->As<T>() : nullptr;
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
