#pragma once

#include <stdexcept>

namespace Engine
{
    class ApplicationNotYetInitialized final : public std::runtime_error
    {
    public:
        ApplicationNotYetInitialized()
            : std::runtime_error("Cannot execute this operation initializing application") {}
    };
}
