#pragma once

#include "Entity.h"
#include "Base/Updatable.h"

namespace TGL
{
    class Component : public Object, public Updatable
    {
    private:
        friend class EntityManager;
        friend class Entity;

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
