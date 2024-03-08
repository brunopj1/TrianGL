#pragma once

#include <stdexcept>

namespace Engine::Exceptions::Game
{
    class GameModeAlreadySpecifiedException final : public std::runtime_error
    {
    public:
        GameModeAlreadySpecifiedException()
            : std::runtime_error("The Game mode has already been specified") {}
    };
}
