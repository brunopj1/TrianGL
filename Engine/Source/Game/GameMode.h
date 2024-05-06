#pragma once

#include <Game/Entity.h>

namespace TGL
{
    class GameMode : public GameObject
    {
    private:
        friend class Application;
        friend class EntityManager;

    protected:
        GameMode();
        ~GameMode() override;

    public:
        virtual void OnEarlyUpdate(float deltaTime);
        virtual void OnLateUpdate(float deltaTime);

    public:
        static GameMode* GetInstance();
    };
}
