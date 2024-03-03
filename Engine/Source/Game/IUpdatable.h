#pragma once

// Forward declarations
namespace Engine::Core
{
    class EntityManager;
}

namespace Engine::Game
{
    // Forward declarations
    class Component;
    class Entity;

    class IUpdatable
    {
    private:
        friend class Core::EntityManager;
        friend class Entity;
        friend class Component;

    private:
        bool m_ShouldUpdate;

    private:
        IUpdatable(bool shouldUpdate);
        virtual ~IUpdatable() = default;

    protected:
        virtual int GetOrderOfExecution() const;

    protected:
        virtual void OnStart();
        virtual void OnUpdate();
    };
}
