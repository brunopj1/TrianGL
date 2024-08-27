#include "Core/DataTypes.h"
#include "Core/Internal/RenderLayer.h"
#include <ASsets/Texture.h>

#include <stb_image.h>
#include <Core/AssetManager.h>
#include <Exceptions/Common/FileNotFoundException.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace TGL;

void Sprite::Unbind(const u8 slot)
{
    RenderLayer::UnbindTexture(slot);
}

TextureSliceInfo::TextureSliceInfo(const glm::uvec2& resolution, const glm::uvec2& offset, const glm::mat4& textureMatrix)
    : Resolution(resolution), Offset(offset), TextureMatrix(textureMatrix)
{}

TextureSlice::TextureSlice(SharedPtr<Texture> texture, const u32 index)
    : m_Texture(std::move(texture)), m_Index(index)
{}

TextureSlice::~TextureSlice()
{
    ASSERT_SPAWNER_USAGE_DESTRUCTOR(TGL::SharedPtrSpawnerUtil, Asset);
}

SharedPtr<Texture> TextureSlice::GetTexture() const
{
    return m_Texture;
}

glm::uvec2 TextureSlice::GetResolution() const
{
    return m_Texture->m_Slices[m_Index].Resolution;
}

void TextureSlice::Bind(const u8 slot) const
{
    RenderLayer::BindTexture(m_Texture->m_TextureId, slot);
}

glm::mat4* TextureSlice::GetMatrix() const
{
    return &m_Texture->m_Slices[m_Index].TextureMatrix;
}

Texture::Texture(std::string filePath)
    : m_FilePath(std::move(filePath))
{
    ASSERT_SPAWNER_USAGE_CONSTRUCTOR(TGL::AssetManager, Texture);
}

Texture::~Texture()
{
    ASSERT_SPAWNER_USAGE_DESTRUCTOR(TGL::SharedPtrSpawnerUtil, Asset);

    AssetManager::UnloadTexture(this);
}

SharedPtr<Texture> Texture::Load(const std::string& filePath, const TextureParameters& parameters)
{
    return AssetManager::LoadTexture(filePath, parameters);
}

std::string Texture::GetFilePath() const
{
    return m_FilePath;
}

glm::uvec2 Texture::GetResolution() const
{
    return m_Resolution;
}

size_t Texture::GetSliceCount() const
{
    return m_Slices.size();
}

SharedPtr<TextureSlice> Texture::GetSlice(const u32 index)
{
    if (index >= m_Slices.size())
    {
        throw std::runtime_error("Invalid slice index");
    }

    return AssetManager::CreateTextureSlice(ToSharedPtr(), index);
}

u32 Texture::CreateSlice(const glm::uvec2& resolution, const glm::uvec2& offset)
{
    const glm::uvec2 topRight = offset + resolution;
    if (topRight.x > m_Resolution.x || topRight.y > m_Resolution.y)
    {
        throw std::runtime_error("Invalid resolution or offset");
    }

    CreateSliceInternal(resolution, offset);

    return static_cast<u32>(m_Slices.size()) - 1;
}

SharedPtr<TextureSlice> Texture::CreateAndGetSlice(const glm::uvec2& resolution, const glm::uvec2& offset)
{
    const i32 index = CreateSlice(resolution, offset);
    return GetSlice(index);
}

u32 Texture::CreateSliceGrid(const glm::uvec2& resolution, const glm::uvec2& padding, const glm::uvec2& spacing)
{
    const glm::uvec2 totalPadding = padding * 2u;
    if (totalPadding.x >= m_Resolution.x || totalPadding.y >= m_Resolution.y)
    {
        throw std::runtime_error("Invalid padding");
    }

    const glm::uvec2 contentResolution = m_Resolution - totalPadding + spacing;
    const glm::uvec2 effectiveSliceResolution = resolution + spacing;
    const glm::uvec2 contentRemainder = contentResolution % effectiveSliceResolution;
    if (contentRemainder.x != 0 || contentRemainder.y != 0)
    {
        throw std::runtime_error("Invalid resolution or spacing");
    }

    const glm::uvec2 sliceCount = contentResolution / effectiveSliceResolution;

    for (u32 y = 0; y < sliceCount.y; y++)
    {
        for (u32 x = 0; x < sliceCount.x; x++)
        {
            const glm::uvec2 offset = padding + effectiveSliceResolution * glm::uvec2(x, y);
            CreateSliceInternal(resolution, offset);
        }
    }

    return sliceCount.x * sliceCount.y;
}

std::vector<SharedPtr<TextureSlice>> Texture::CreateAndGetSliceGrid(const glm::uvec2& resolution, const glm::uvec2& padding, const glm::uvec2& spacing)
{
    const u32 sliceCount = CreateSliceGrid(resolution, padding, spacing);

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
    const glm::vec3 translate = {
        offset.x / static_cast<f32>(m_Resolution.x),
        (m_Resolution.y - resolution.y - offset.y) / static_cast<f32>(m_Resolution.y),
        0.0f
    };

    const glm::vec3 scale = {
        resolution.x / static_cast<f32>(m_Resolution.x),
        resolution.y / static_cast<f32>(m_Resolution.y),
        1.0f
    };

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

    RenderLayer::GenerateTexture(m_TextureId);

    RenderLayer::SetTextureWrapMode(parameters.Wrap);
    RenderLayer::SetTextureFilterMode(parameters.Filter, parameters.MipmapFilter, parameters.GenerateMipmaps);

    RenderLayer::SetTextureData(m_Resolution, data);

    if (parameters.GenerateMipmaps)
    {
        RenderLayer::GenerateTextureMipmaps();
    }

    stbi_image_free(data);
}

void Texture::Free()
{
    RenderLayer::DeleteTexture(m_TextureId);
    m_TextureId = 0;
}

void Texture::Bind(const u8 slot) const
{
    RenderLayer::BindTexture(m_TextureId, slot);
}

glm::mat4* Texture::GetMatrix() const
{
    return nullptr;
}
