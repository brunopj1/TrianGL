#pragma once

#include "TextureParameters.hpp"
#include "glm/mat2x2.hpp"
#include "glm/vec2.hpp"
#include "Util/Macros/SpawnerMacros.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace TGL
{
    // Binding class (for the material attribute)

    class TextureBinding
    {
    private:
        friend class TextureMaterialAttribute;

    protected:
        TextureBinding() = default;
        virtual ~TextureBinding() = default;

    private:
        virtual void Bind(unsigned int slot) const = 0;
        virtual glm::mat4* GetMatrix() const = 0;
    };

    // Texture slice struct and class

    struct TextureSliceInfo
    {
    private:
        friend class Texture;
        friend class TextureSlice;

    private:
        glm::uvec2 Resolution;
        glm::uvec2 Offset;
        glm::mat4 TextureMatrix;

    private:
        TextureSliceInfo(const glm::uvec2& resolution, const glm::uvec2& offset, const glm::mat4& textureMatrix);
    };

    class TextureSlice final : public TextureBinding
    {
    private:
        friend class Texture;

    private:
        DECLARE_SPAWNER_USAGE_VAR();

    private:
        std::shared_ptr<Texture> m_Texture;
        int m_Index;

    public:
        TextureSlice(std::shared_ptr<Texture> texture, int index);
        ~TextureSlice() override = default;

    private:
        void Bind(unsigned slot) const override;
        glm::mat4* GetMatrix() const override;
    };

    // Main class-

    class Texture final : public TextureBinding, public std::enable_shared_from_this<Texture>
    {
    private:
        friend class ResourceManager;
        friend class TextureSlice;
        friend class TextureMaterialAttribute;

    private:
        DECLARE_SPAWNER_USAGE_VAR();

    private:
        std::string m_FilePath;
        unsigned int m_TextureId = 0;
        glm::uvec2 m_Resolution = {0, 0};
        bool m_HasTransparency = false;

    private:
        std::vector<TextureSliceInfo> m_Slices;

    public:
        Texture(std::string filePath, const TextureParameters& parameters = {});
        ~Texture() override;

    public:
        static std::shared_ptr<Texture> Load(std::string filePath, const TextureParameters& parameters = {});

    public:
        std::string GetFilePath() const;
        glm::uvec2 GetResolution() const;
        bool HasTransparency() const;

    public:
        size_t SliceCount() const;
        std::shared_ptr<TextureSlice> GetSlice(unsigned int index);

        int CreateSlice(const glm::uvec2& resolution, const glm::uvec2& offset); // Returns the slice index
        std::shared_ptr<TextureSlice> CreateAndGetSlice(const glm::uvec2& resolution, const glm::uvec2& offset);

        int CreateSliceGrid(const glm::uvec2& resolution, const glm::uvec2& padding = {0, 0}, const glm::uvec2& spacing = {0, 0}); // Returns the slice index
        std::vector<std::shared_ptr<TextureSlice>> CreateAndGetSliceGrid(const glm::uvec2& resolution, const glm::uvec2& padding = {0, 0}, const glm::uvec2& spacing = {0, 0});

    private:
        void CreateSliceInternal(const glm::uvec2& resolution, const glm::uvec2& offset);

    private:
        void Load(const TextureParameters& parameters);
        void Free();

    private:
        void Bind(unsigned slot) const override;
        glm::mat4* GetMatrix() const override;
    };
}
