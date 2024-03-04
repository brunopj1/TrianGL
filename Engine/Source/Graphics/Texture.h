#pragma once

#include "TextureParameters.hpp"
#include "glm/vec2.hpp"
#include <string>

// Forward declaration
namespace Engine::Components
{
    class TextureRenderer;
}

namespace Engine::Graphics
{
    struct TextureParameters
    {
        bool GenerateMipmaps = true;
        TextureWrapMode Wrap = TextureWrapMode::Repeat;
        TextureFilterMode Filter = TextureFilterMode::Linear;
        TextureFilterMode MipmapFilter = TextureFilterMode::Linear;
    };

    class Texture
    {
    private:
        friend class Components::TextureRenderer;

    private:
        std::string m_FilePath;
        unsigned int m_TextureId = 0;
        glm::uvec2 m_Resolution = {0, 0};
        bool m_HasTransparency = false;

    private:
        Texture(std::string filePath, const TextureParameters& parameters = {});
        ~Texture();

    public:
        std::string GetFilePath() const;
        glm::uvec2 GetResolution() const;
        bool HasTransparency() const;

    private:
        void Load(const TextureParameters& parameters);
        void Free();

    private:
        void Bind(int slot = 0) const;
    };
}
