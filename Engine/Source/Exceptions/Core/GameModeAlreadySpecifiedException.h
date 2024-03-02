#pragma once

#include <exception>

namespace Engine::Exceptions::Core
{
    class GameModeAlreadySpecifiedException final : public std::exception
    {
    public:
        GameModeAlreadySpecifiedException() = default;
        ~GameModeAlreadySpecifiedException() override = default;

    public:
        [[nodiscard]] const char* what() const override;
    };
}
