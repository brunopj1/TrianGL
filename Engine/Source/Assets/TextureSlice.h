#pragma once

#include "Internal/Sprite.h"
#include "Memory/SharedPtr.h"
#include "glm/mat4x4.hpp"
#include "glm/vec2.hpp"

namespace TGL
{
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
		bool Bind(u8 slot) const override;
		const glm::mat4& GetMatrix() const override;
	};
}
