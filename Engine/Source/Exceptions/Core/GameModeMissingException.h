#pragma once

#include <exception>

namespace Engine::Exceptions::Core
{
    class GameModeMissingException final : public std::exception
    {
    public:
        GameModeMissingException() = default;

    public:
        [[nodiscard]] const char* what() const override;
    };
}
