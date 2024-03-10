#pragma once

#include "Internal/ManagedResource.h"
#include "TextureParameters.hpp"
#include "glm/vec2.hpp"
#include "Util/Macros/SpawnerMacros.hpp"
#include <string>

namespace Engine
{
    class Texture final : public ManagedResource
    {
    private:
        friend class ResourceManager;
        friend class TextureMaterialAttribute;

    private:
        DECLARE_SPAWNER_USAGE_VAR();

    private:
        std::string m_FilePath;
        unsigned int m_TextureId = 0;
        glm::uvec2 m_Resolution = {0, 0};
        bool m_HasTransparency = false;

    private:
        Texture(std::string filePath, const TextureParameters& parameters = {});
        ~Texture() override;

    public:
        static Texture* Load(std::string filePath, const TextureParameters& parameters = {});
        void Unload() override;

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
