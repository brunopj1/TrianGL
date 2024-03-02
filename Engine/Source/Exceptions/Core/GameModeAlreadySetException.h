#pragma once

#include <exception>

namespace Engine::Exceptions::Core
{
    class GameModeAlreadySetException final : public std::exception
    {
    public:
        GameModeAlreadySetException() = default;
        ~GameModeAlreadySetException() override = default;

    public:
        [[nodiscard]] const char* what() const override;
    };
}
