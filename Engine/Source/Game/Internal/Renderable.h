#pragma once
#include "Game/Transform.h"

// Forward declarations
namespace Engine::Services
{
    class EntityManager;
}

namespace Engine::Game::Internal
{
    class Renderable
    {
    private:
        friend class Services::EntityManager;

    private:
        Transform m_Transform;
        int m_ZIndex = 0;

    public:
        Renderable() = default;
        virtual ~Renderable() = default;

    public:
        Transform& GetTransform();
        const Transform& GetTransform() const;

        int GetZIndex() const;
        void SetZIndex(int zIndex);

    protected:
        virtual void Render() = 0;
    };
}
