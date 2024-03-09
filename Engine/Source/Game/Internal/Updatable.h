#pragma once

// Forward declarations
namespace Engine::Services
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
    class Updatable
    {
    private:
        friend class Services::EntityManager;

    private:
        bool m_ShouldUpdate;

    public:
        Updatable(bool shouldUpdate);
        virtual ~Updatable() = default;

    protected:
        virtual int GetOrderOfExecution() const;

    protected:
        virtual void OnStart();
        virtual void OnUpdate(float deltaTime);
    };
}
