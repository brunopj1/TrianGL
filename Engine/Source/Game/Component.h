#pragma once

#include "Entity.h"

namespace TGL
{
    class Component : public GameObject
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
