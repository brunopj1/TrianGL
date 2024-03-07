#pragma once

#include "Internal/ManagedResource.h"
#include "TextureParameters.hpp"
#include "glm/vec2.hpp"
#include <string>

// Forward declaration
namespace Engine::Services
{
    class ResourceManager;
}

namespace Engine::Components
{
    class TextureRenderer;
}

namespace Engine::Resources
{
    class Texture final : public Internal::ManagedResource
    {
    private:
        friend class Services::ResourceManager;
        friend class TextureMaterialAttribute;

    private:
        std::string m_FilePath;
        unsigned int m_TextureId = 0;
        glm::uvec2 m_Resolution = {0, 0};
        bool m_HasTransparency = false;

    private:
        Texture(std::string filePath, const TextureParameters& parameters = {});
        ~Texture() override;

    public:
        std::string GetFilePath() const;
        glm::uvec2 GetResolution() const;
        bool HasTransparency() const;

    private:
        void Load(const TextureParameters& parameters);
        void Free();

    private:
        void Bind(unsigned int slot) const;
    };
}
