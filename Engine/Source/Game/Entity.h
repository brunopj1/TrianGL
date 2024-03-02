#pragma once

// Forward declarations
namespace Engine::Core
{
    class EntityManager;
}

namespace Engine::Game
{
    // TODO order of execution system
    class Entity
    {
    private:
        friend class Core::EntityManager;

    protected:
        Entity() = default;
        virtual ~Entity() = default;

    public:
        virtual void OnStart();
        virtual void OnUpdate();
    };
}
