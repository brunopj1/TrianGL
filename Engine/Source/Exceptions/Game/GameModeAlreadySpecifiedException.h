#pragma once

#include <stdexcept>

namespace TGL
{
    class GameModeAlreadySpecifiedException final : public std::runtime_error
    {
    public:
        GameModeAlreadySpecifiedException()
            : std::runtime_error("The Game mode has already been specified") {}
    };
}
