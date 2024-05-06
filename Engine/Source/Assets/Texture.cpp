#include <ASsets/Texture.h>

#include <glad/glad.h>
#include <stb_image.h>
#include <Core/AssetManager.h>
#include <Exceptions/Common/FileNotFoundException.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace TGL;

void Sprite::Unbind(const unsigned char slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, 0);
}

TextureSliceInfo::TextureSliceInfo(const glm::uvec2& resolution, const glm::uvec2& offset, const glm::mat4& textureMatrix)
    : Resolution(resolution), Offset(offset), TextureMatrix(textureMatrix)
{}

TextureSlice::TextureSlice(SharedPtr<Texture> texture, const int index)
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

void TextureSlice::Bind(const unsigned char slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_Texture->m_TextureId);
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

SharedPtr<TextureSlice> Texture::GetSlice(const unsigned int index)
{
    if (index >= m_Slices.size())
    {
        throw std::runtime_error("Invalid slice index");
    }

    return AssetManager::CreateTextureSlice(ToSharedPtr(), index);
}

int Texture::CreateSlice(const glm::uvec2& resolution, const glm::uvec2& offset)
{
    const glm::uvec2 topRight = offset + resolution;
    if (topRight.x > m_Resolution.x || topRight.y > m_Resolution.y)
    {
        throw std::runtime_error("Invalid resolution or offset");
    }

    CreateSliceInternal(resolution, offset);

    return static_cast<int>(m_Slices.size()) - 1;
}

SharedPtr<TextureSlice> Texture::CreateAndGetSlice(const glm::uvec2& resolution, const glm::uvec2& offset)
{
    const int index = CreateSlice(resolution, offset);
    return GetSlice(index);
}

int Texture::CreateSliceGrid(const glm::uvec2& resolution, const glm::uvec2& padding, const glm::uvec2& spacing)
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

    for (unsigned int y = 0; y < sliceCount.y; y++)
    {
        for (unsigned int x = 0; x < sliceCount.x; x++)
        {
            const glm::uvec2 offset = padding + effectiveSliceResolution * glm::uvec2(x, y);
            CreateSliceInternal(resolution, offset);
        }
    }

    return sliceCount.x * sliceCount.y;
}

std::vector<SharedPtr<TextureSlice>> Texture::CreateAndGetSliceGrid(const glm::uvec2& resolution, const glm::uvec2& padding, const glm::uvec2& spacing)
{
    const int sliceCount = CreateSliceGrid(resolution, padding, spacing);

    std::vector<SharedPtr<TextureSlice>> slices;
    slices.reserve(sliceCount);

    for (int i = static_cast<int>(m_Slices.size()) - sliceCount; i < m_Slices.size(); i++)
    {
        slices.push_back(GetSlice(i));
    }

    return slices;
}

void Texture::CreateSliceInternal(const glm::uvec2& resolution, const glm::uvec2& offset)
{
    const glm::vec3 translate = {
        offset.x / static_cast<float>(m_Resolution.x),
        (m_Resolution.y - resolution.y - offset.y) / static_cast<float>(m_Resolution.y),
        0.0f
    };

    const glm::vec3 scale = {
        resolution.x / static_cast<float>(m_Resolution.x),
        resolution.y / static_cast<float>(m_Resolution.y),
        1.0f
    };

    glm::mat4 textureMatrix = glm::translate(glm::mat4(1.0f), translate);
    textureMatrix = glm::scale(textureMatrix, scale);

    m_Slices.push_back({resolution, offset, textureMatrix});
}

void Texture::Init(const TextureParameters& parameters)
{
    int width, height, channels;
    unsigned char* data = stbi_load(m_FilePath.c_str(), &width, &height, &channels, 0);
    if (!data)
    {
        throw FileNotFoundException(m_FilePath);
    }

    m_Resolution = {width, height};

    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    int glWrapParameter = 0;

    switch (parameters.Wrap)
    {
        case TextureWrapMode::Repeat:
            glWrapParameter = GL_REPEAT;
            break;
        case TextureWrapMode::MirroredRepeat:
            glWrapParameter = GL_MIRRORED_REPEAT;
            break;
        case TextureWrapMode::ClampToEdge:
            glWrapParameter = GL_CLAMP_TO_EDGE;
            break;
        case TextureWrapMode::ClampToBorder:
            glWrapParameter = GL_CLAMP_TO_BORDER;
            break;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrapParameter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrapParameter);

    const int glMagFilterParameter = parameters.Filter == TextureFilterMode::Linear ? GL_LINEAR : GL_NEAREST;
    int glMinFilterParameter = glMagFilterParameter;

    if (parameters.GenerateMipmaps)
    {
        if (parameters.Filter == TextureFilterMode::Linear)
        {
            glMinFilterParameter = parameters.MipmapFilter == TextureFilterMode::Linear ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_NEAREST;
        }
        else // (parameters.Filter == TextureFilterMode::Nearest)
        {
            glMinFilterParameter = parameters.MipmapFilter == TextureFilterMode::Linear ? GL_NEAREST_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_NEAREST;
        }
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glMinFilterParameter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glMagFilterParameter);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    if (parameters.GenerateMipmaps)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);
}

void Texture::Free()
{
    glDeleteTextures(1, &m_TextureId);
    m_TextureId = 0;
}

void Texture::Bind(const unsigned char slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

glm::mat4* Texture::GetMatrix() const
{
    return nullptr;
}
