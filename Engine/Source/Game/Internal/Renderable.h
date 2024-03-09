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

    public:
        Renderable() = default;
        virtual ~Renderable() = default;

    public:
        Transform& GetTransform();
        const Transform& GetTransform() const;

    protected:
        virtual void Render() = 0;
    };
}
