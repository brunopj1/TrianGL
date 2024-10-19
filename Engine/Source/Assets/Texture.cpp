#include "Core/DataTypes.h"
#include "Core/Services/Backends/RenderBackend.h"
#include <ASsets/Texture.h>
#include <Core/Services/Private/AssetManager.h>
#include <Exceptions/Common/FileNotFoundException.h>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

using namespace TGL;

Texture::Texture(std::string filePath)
	: m_FilePath(std::move(filePath))
{
	ASSERT_ASSET_FACTORY_CONSTRUCTOR(Texture);
}

Texture::~Texture()
{
	ASSERT_ASSET_FACTORY_DESTRUCTOR();

	Free();
}

SharedPtr<Texture> Texture::Load(const std::string& filePath, const TextureParameters& parameters)
{
	AssetManager& assetManager = AssetManager::Get();
	return assetManager.LoadTexture(filePath, parameters);
}

std::string Texture::GetFilePath() const
{
	return m_FilePath;
}

const glm::uvec2& Texture::GetResolution() const
{
	return m_Resolution;
}

size_t Texture::GetSliceCount() const
{
	return m_Slices.size();
}

SharedPtr<TextureSlice> Texture::GetSlice(const u32 index) const
{
	if (index >= m_Slices.size())
	{
		throw std::runtime_error("Invalid slice index");
	} 

	AssetManager& assetManager = AssetManager::Get();
	return assetManager.CreateTextureSlice(ToSharedPtr(), index);
}

u32 Texture::CreateSlice(const glm::uvec2& resolution, const glm::uvec2& offset)
{
	if (resolution.x <= 0 || resolution.y <= 0 || resolution.x > m_Resolution.x || resolution.y > m_Resolution.y)
	{
		throw std::invalid_argument("Invalid resolution");
	}

	if (offset.x < 0 || offset.y < 0 || offset.x >= m_Resolution.x || offset.y >= m_Resolution.y)
	{
		throw std::invalid_argument("Invalid offset");
	}

	const glm::uvec2 corner = offset + resolution;
	if (corner.x > m_Resolution.x || corner.y > m_Resolution.y)
	{
		throw std::invalid_argument("Invalid bounds");
	}

	CreateSliceInternal(resolution, offset);

	return static_cast<u32>(m_Slices.size()) - 1;
}

SharedPtr<TextureSlice> Texture::CreateAndGetSlice(const glm::uvec2& resolution, const glm::uvec2& offset)
{
	const i32 index = CreateSlice(resolution, offset);
	return GetSlice(index);
}

u32 Texture::CreateSliceGrid(const glm::uvec2& resolution, const glm::uvec2& offset, const glm::uvec2& spacing)
{
	if (resolution.x <= 0 || resolution.y <= 0 || resolution.x > m_Resolution.x || resolution.y > m_Resolution.y)
	{
		throw std::invalid_argument("Invalid resolution");
	}

	if (offset.x < 0 || offset.y < 0 || offset.x >= m_Resolution.x || offset.y >= m_Resolution.y)
	{
		throw std::invalid_argument("Invalid offset");
	}

	if (spacing.x < 0 || spacing.y < 0 || spacing.x >= resolution.x || spacing.y >= resolution.y)
	{
		throw std::invalid_argument("Invalid spacing");
	}

	const glm::uvec2 effectiveContentResolution = m_Resolution - offset + spacing;
	const glm::uvec2 effectiveSliceResolution = resolution + spacing;

	const glm::uvec2 sliceCount = effectiveContentResolution / effectiveSliceResolution;
	if (sliceCount.x == 0 || sliceCount.y == 0)
	{
		throw std::invalid_argument("Invalid bounds");
	}

	for (u32 y = 0; y < sliceCount.y; y++)
	{
		for (u32 x = 0; x < sliceCount.x; x++)
		{
			const glm::uvec2 sliceOffset = offset + effectiveSliceResolution * glm::uvec2(x, y);
			CreateSliceInternal(resolution, sliceOffset);
		}
	}

	return sliceCount.x * sliceCount.y;
}

std::vector<SharedPtr<TextureSlice>> Texture::CreateAndGetSliceGrid(const glm::uvec2& resolution, const glm::uvec2& offset, const glm::uvec2& spacing)
{
	const u32 sliceCount = CreateSliceGrid(resolution, offset, spacing);

	std::vector<SharedPtr<TextureSlice>> slices;
	slices.reserve(sliceCount);

	for (u32 i = static_cast<u32>(m_Slices.size()) - sliceCount; i < m_Slices.size(); i++)
	{
		slices.push_back(GetSlice(i));
	}

	return slices;
}

void Texture::CreateSliceInternal(const glm::uvec2& resolution, const glm::uvec2& offset)
{
	const glm::vec3 translate = {offset.x / static_cast<f32>(m_Resolution.x), (m_Resolution.y - resolution.y - offset.y) / static_cast<f32>(m_Resolution.y), 0.0f};

	const glm::vec3 scale = {resolution.x / static_cast<f32>(m_Resolution.x), resolution.y / static_cast<f32>(m_Resolution.y), 1.0f};

	glm::mat4 textureMatrix = glm::translate(glm::mat4(1.0f), translate);
	textureMatrix = glm::scale(textureMatrix, scale);

	m_Slices.push_back({resolution, offset, textureMatrix});
}

void Texture::Init(const TextureParameters& parameters)
{
	i32 width, height, channels;
	u8* data = stbi_load(m_FilePath.c_str(), &width, &height, &channels, 0);
	if (!data)
	{
		throw FileNotFoundException(m_FilePath);
	}

	m_Resolution = {width, height};

	RenderBackend& renderBackend = RenderBackend::Get();

	renderBackend.GenerateTexture(m_TextureId);

	renderBackend.SetTextureWrapMode(parameters.Wrap);
	renderBackend.SetTextureFilterMode(parameters.Filter, parameters.MipmapFilter, parameters.GenerateMipmaps);

	renderBackend.SetTextureData(m_Resolution, data);

	if (parameters.GenerateMipmaps)
	{
		renderBackend.GenerateTextureMipmaps();
	}

	stbi_image_free(data);
}

void Texture::Free()
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.DeleteTexture(m_TextureId);
	m_TextureId = 0;
}

bool Texture::Bind(const u8 slot) const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.BindTexture(m_TextureId, slot);
	return true;
}

const glm::mat4& Texture::GetMatrix() const
{
	return s_Matrix;
}
