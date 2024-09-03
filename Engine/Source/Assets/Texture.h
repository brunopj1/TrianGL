#pragma once

#include <Memory/SharedPtr.h>
#include <glm/mat2x2.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <vector>

namespace TGL
{
	// clang-format off
    
    enum class TextureWrapMode : u16
    {
        Repeat         = 0x2901, // GL_REPEAT
        MirroredRepeat = 0x8370, // GL_MIRRORED_REPEAT
        ClampToEdge    = 0x812F, // GL_CLAMP_TO_EDGE
        ClampToBorder  = 0x812D  // GL_CLAMP_TO_BORDER
    };

    enum class TextureFilterMode : u16
    {
        Nearest = 0x2600, // GL_NEAREST
        Linear  = 0x2601  // GL_LINEAR
    };

	// clang-format on

	struct TextureParameters
	{
		bool GenerateMipmaps = true;
		TextureWrapMode Wrap = TextureWrapMode::Repeat;
		TextureFilterMode Filter = TextureFilterMode::Linear;
		TextureFilterMode MipmapFilter = TextureFilterMode::Linear;
	};

	class Sprite
	{
	private:
		friend class SpriteUniform;

	public:
		Sprite() = default;
		virtual ~Sprite() = default;

	private:
		static void Unbind(u8 slot);
		virtual void Bind(u8 slot) const = 0;

		virtual const glm::mat4& GetMatrix() const = 0;
		virtual const glm::uvec2& GetResolution() const = 0;
	};

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

	class TextureSlice final : public Sprite
	{
	private:
		friend class Texture;

	private:
		SharedPtr<Texture> m_Texture;
		i32 m_Index;

	public:
		TextureSlice(SharedPtr<Texture> texture, u32 index);
		~TextureSlice() override;

	public:
		SharedPtr<Texture> GetTexture() const;
		const glm::uvec2& GetResolution() const override; // Also used by Sprite class

	private:
		void Bind(u8 slot) const override;
		const glm::mat4& GetMatrix() const override;
	};

	// Main class-

	class Texture final : public Sprite, public SharedFromThis<Texture>
	{
	private:
		friend class AssetManager;
		friend class TextureSlice;
		friend class SpriteUniform;

	private:
		static inline glm::mat4 s_Matrix = glm::mat4(1.0f);

	private:
		std::string m_FilePath;
		u32 m_TextureId = 0;
		glm::uvec2 m_Resolution = {0, 0};

	private:
		std::vector<TextureSliceInfo> m_Slices;

	public:
		Texture(std::string filePath);
		~Texture() override;

	public:
		static SharedPtr<Texture> Load(const std::string& filePath, const TextureParameters& parameters = {});

	public:
		std::string GetFilePath() const;
		const glm::uvec2& GetResolution() const override; // Also used by Sprite class

	public:
		size_t GetSliceCount() const;
		SharedPtr<TextureSlice> GetSlice(u32 index);

		u32 CreateSlice(const glm::uvec2& resolution, const glm::uvec2& offset); // Returns the slice index
		SharedPtr<TextureSlice> CreateAndGetSlice(const glm::uvec2& resolution, const glm::uvec2& offset);

		u32 CreateSliceGrid(const glm::uvec2& resolution, const glm::uvec2& padding = {0, 0}, const glm::uvec2& spacing = {0, 0}); // Returns the slice index
		std::vector<SharedPtr<TextureSlice>> CreateAndGetSliceGrid(const glm::uvec2& resolution, const glm::uvec2& padding = {0, 0}, const glm::uvec2& spacing = {0, 0});

	private:
		void CreateSliceInternal(const glm::uvec2& resolution, const glm::uvec2& offset);

	private:
		void Init(const TextureParameters& parameters);
		void Free();

	private:
		void Bind(u8 slot) const override;
		const glm::mat4& GetMatrix() const override;
	};
}
