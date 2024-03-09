#pragma once
#include <type_traits>

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

    public:
        template <typename T, typename = std::enable_if_t<std::is_base_of_v<GameMode, T>>>
        T* As()
        {
            return dynamic_cast<T*>(this);
        }
    };
}
