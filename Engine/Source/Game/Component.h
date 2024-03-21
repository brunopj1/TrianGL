#pragma once

#include "Entity.h"
#include "Base/Updatable.h"
#include <type_traits>

namespace TGL
{
    // Forward declarations
    template <typename T, typename C>
    class LazyPtr;

    class Component : public Object, public Updatable
    {
    private:
        friend class EntityManager;
        friend class Entity;

        template <typename T, typename C>
        friend class LazyPtr;

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
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::Entity)>
        static T* SpawnEntity(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            return Entity::SpawnEntity<T>(std::forward<Args>(args)...);
        }

        void Detach();
    };
}
