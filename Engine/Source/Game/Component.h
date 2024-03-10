#pragma once

#include "Entity.h"
#include "Internal/Updatable.h"
#include <type_traits>

namespace Engine::Core
{
    class EntityManager;
}

namespace Engine::Game
{
    // Forward declarations
    class Entity;

    class Component : public Internal::Updatable
    {
    private:
        friend class Entity;

    private:
        DECLARE_SPAWNER_USAGE_VAR();

    private:
        Entity* m_Parent = nullptr;

    protected:
        Component(bool shouldUpdate);
        ~Component() override;

    public:
        Entity* GetParent() const;

    public:
        template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
        T* As()
        {
            return dynamic_cast<T*>(this);
        }

    public:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(Engine::Game::Entity)>
        static T* SpawnEntity(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            return Entity::SpawnEntity<T>(std::forward<Args>(args)...);
        }

        void Detach();
    };
}
