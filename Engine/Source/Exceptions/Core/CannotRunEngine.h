#pragma once

#include <stdexcept>
#include <string>

namespace TGL
{
    class CannotRunEngine final : public std::runtime_error
    {
    public:
        CannotRunEngine()
            : std::runtime_error("Cannot run the the same engine instance more than once") {}
    };
}
