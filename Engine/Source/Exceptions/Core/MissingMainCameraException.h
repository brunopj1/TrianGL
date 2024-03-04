#pragma once

#include <exception>

namespace Engine::Exceptions::Core
{
    class MissingMainCameraException final : public std::exception
    {
    public:
        MissingMainCameraException() = default;
        ~MissingMainCameraException() override = default;

    public:
        [[nodiscard]] const char* what() const override;
    };
}
