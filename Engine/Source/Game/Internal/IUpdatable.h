#pragma once

// Forward declarations
namespace Engine::Core
{
    class EntityManager;
}

namespace Engine::Game
{
    class Component;
    class Entity;
}

namespace Engine::Game::Internal
{
    class IUpdatable
    {
    private:
        friend class Core::EntityManager;

    private:
        bool m_ShouldUpdate;

    public:
        IUpdatable(bool shouldUpdate);
        virtual ~IUpdatable() = default;

    protected:
        virtual int GetOrderOfExecution() const;

    protected:
        virtual void OnStart();
        virtual void OnUpdate();
    };
}
