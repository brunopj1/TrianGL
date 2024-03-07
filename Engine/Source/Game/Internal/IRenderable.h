﻿#pragma once

// Forward declarations
namespace Engine::Core
{
    class EntityManager;
}

namespace Engine::Game::Internal
{
    class IRenderable
    {
    private:
        friend class Core::EntityManager;

    private:
        bool m_ShouldUpdate;

    public:
        IRenderable() = default;
        virtual ~IRenderable() = default;

    protected:
        virtual void Render() const = 0;
    };
}
