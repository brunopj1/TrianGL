#pragma once

#include "TextureParameters.hpp"
#include "glm/vec2.hpp"
#include "Util/Macros/SpawnerMacros.hpp"
#include <memory>
#include <string>

namespace TGL
{
    class Texture final
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

    public:
        Texture(std::string filePath, const TextureParameters& parameters = {});
        ~Texture();

    public:
        static std::shared_ptr<Texture> Load(std::string filePath, const TextureParameters& parameters = {});

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
