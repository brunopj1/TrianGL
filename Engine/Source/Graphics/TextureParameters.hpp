#pragma once

namespace Engine::Graphics
{
    enum class TextureWrapMode
    {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
        ClampToBorder
    };

    enum class TextureFilterMode
    {
        Nearest,
        Linear
    };
}
