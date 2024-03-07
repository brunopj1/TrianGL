#pragma once

namespace Engine::Game
{
    class GameMode
    {
    public:
        GameMode();
        virtual ~GameMode();

    public:
        virtual void OnStart();
        virtual void OnEarlyUpdate(float deltaTime);
        virtual void OnLateUpdate(float deltaTime);
    };
}
