#pragma once

#include <stdexcept>

namespace Engine::Exceptions::Game
{
    class MissingMainCameraException final : public std::runtime_error
    {
    public:
        MissingMainCameraException()
            : std::runtime_error("Cannot play without a main camera") {}
    };
}
