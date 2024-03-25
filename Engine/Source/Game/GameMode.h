#pragma once

#include "Entity.h"

namespace TGL
{
    class GameMode : public Object
    {
    private:
        friend class Application;
        friend class EntityManager;

    public:
        GameMode();
        ~GameMode() override;

    public:
        virtual void OnEarlyUpdate(float deltaTime);
        virtual void OnLateUpdate(float deltaTime);

    public:
        static GameMode* GetInstance();
    };
}
