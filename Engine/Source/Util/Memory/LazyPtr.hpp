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
        uint32_t m_Id;

    public:
        LazyPtr(T* value)
        {
            m_Id = value->m_Id;
        }

        LazyPtr(std::nullptr_t)
        {
            m_Id = 0;
        }

        ~LazyPtr() = default;

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
