#pragma once

#include <stdexcept>

namespace TGL
{
    class GameModeMissingException final : public std::runtime_error
    {
    public:
        GameModeMissingException()
            : std::runtime_error("Cannot run the application without a Game mode") {}
    };
}
