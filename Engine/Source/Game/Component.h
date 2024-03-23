#pragma once

#include "Entity.h"
#include "Base/Updatable.h"

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
        Entity* m_Parent = nullptr;

    protected:
        Component(bool shouldUpdate);
        ~Component() override;

    public:
        Entity* GetParent() const;

    public:
        void Detach();
    };
}
