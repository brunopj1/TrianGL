#pragma once

#include "Core/EntityManager.h"
#include "Util/Macros/SpawnerMacros.hpp"
#include <cstdint>

namespace TGL
{
    class Object
    {
    private:
        friend class EntityManager;

    private:
        uint64_t m_Id = 0;

    public:
        Object() = default;
        virtual ~Object() = default;

    public:
        template <typename T, typename = std::enable_if_t<std::is_base_of_v<Object, T>>>
        T* As()
        {
            return dynamic_cast<T*>(this);
        }

    public:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::Entity)>
        static T* SpawnEntity(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            return EntityManager::CreateEntity<T>(std::forward<Args>(args)...);
        }

    public:
        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(TGL::Entity)>
        static T* FindEntityGlobally()
        {
            return EntityManager::FindEntityGlobally<T>();
        }

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(TGL::Entity)>
        static std::vector<T*> FindEntitiesGlobally()
        {
            return EntityManager::FindEntitiesGlobally<T>();
        }


        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(TGL::Component)>
        static T* FindComponentGlobally()
        {
            return EntityManager::FindComponentGlobally<T>();
        }

        template <typename T, typename = SPAWNER_LOOKUP_TEMPLATE_CONDITION(TGL::Component)>
        static std::vector<T*> FindComponentsGlobally()
        {
            return EntityManager::FindComponentsGlobally<T>();
        }
    };
}
