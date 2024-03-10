﻿#pragma once

#include <string>

namespace Engine
{
    // Forward declaration
    class Shader;

    struct ShaderHash
    {
        std::size_t operator()(const Shader* shader) const;
    };

    struct ShaderEqual
    {
        bool operator()(const Shader* shader1, const Shader* shader2) const;
    };
}
