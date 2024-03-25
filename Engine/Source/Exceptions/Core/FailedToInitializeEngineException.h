#pragma once

#include <stdexcept>
#include <string>

namespace TGL
{
    class FailedToInitializeEngineException final : public std::runtime_error
    {
    public:
        FailedToInitializeEngineException(const std::string& message)
            : std::runtime_error(message) {}
    };
}
