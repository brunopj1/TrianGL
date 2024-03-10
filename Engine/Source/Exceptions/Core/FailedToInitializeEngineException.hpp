#pragma once

#include <stdexcept>
#include <string>

namespace Engine
{
    class FailedToInitializeEngineException final : public std::runtime_error
    {
    public:
        FailedToInitializeEngineException(const std::string& message)
            : std::runtime_error(message) {}
    };
}
