#include "TextureSlice.h"

#include "Core/Services/Backends/RenderBackend.h"
#include "Core/Services/Private/AssetManager.h"
#include "Texture.h"

using namespace TGL;

TextureSliceInfo::TextureSliceInfo(const glm::uvec2& resolution, const glm::uvec2& offset, const glm::mat4& textureMatrix)
	: Resolution(resolution), Offset(offset), TextureMatrix(textureMatrix) {}

TextureSlice::TextureSlice(SharedPtr<Texture> texture, const u32 index)
	: m_Texture(std::move(texture)), m_Index(index)
{
	ASSERT_SPAWNER_USAGE_CONSTRUCTOR(AssetManager, TextureSlice);
}

TextureSlice::~TextureSlice()
{
	ASSERT_SPAWNER_USAGE_DESTRUCTOR(TGL::SharedPtrSpawnerUtil, Asset);
}

SharedPtr<Texture> TextureSlice::GetTexture() const
{
	return m_Texture;
}

const glm::uvec2& TextureSlice::GetResolution() const
{
	return m_Texture->m_Slices[m_Index].Resolution;
}

bool TextureSlice::Bind(const u8 slot) const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.BindTexture(m_Texture->m_TextureId, slot);
	return true;
}

const glm::mat4& TextureSlice::GetMatrix() const
{
	return m_Texture->m_Slices[m_Index].TextureMatrix;
}
