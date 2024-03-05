#pragma once

namespace Engine::Resources
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

    struct TextureParameters
    {
        bool GenerateMipmaps = true;
        TextureWrapMode Wrap = TextureWrapMode::Repeat;
        TextureFilterMode Filter = TextureFilterMode::Linear;
        TextureFilterMode MipmapFilter = TextureFilterMode::Linear;
    };
}
