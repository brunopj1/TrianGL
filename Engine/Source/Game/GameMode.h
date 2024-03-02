#pragma once

namespace Engine::Game
{
    class GameMode
    {
    protected:
        GameMode() = default;

    public:
        virtual ~GameMode() = default;

    public:
        virtual void OnStart();
        virtual void OnEarlyUpdate();
        virtual void OnLateUpdate();
    };
}
