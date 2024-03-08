#pragma once

#include <stdexcept>

namespace Engine::Exceptions::Game
{
    class GameModeMissingException final : public std::runtime_error
    {
    public:
        GameModeMissingException()
            : std::runtime_error("Cannot run the application without a Game mode") {}
    };
}
