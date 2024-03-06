﻿#include "Texture.h"

#include "stb_image.h"
#include "Core/ResourceManager.h"

#include "glad/glad.h"

#include "Exceptions/Common/FileNotFoundException.h"
#include "Util/DebugFeatures.hpp"

using namespace Engine::Resources;

Texture::Texture(std::string filePath, const TextureParameters& parameters)
    : m_FilePath(std::move(filePath))
{
    DEBUG_SINGLETON_ASSERT_USAGE(Engine::Core::ResourceManager, "Engine::Resources::Texture");

    Load(parameters);
}

Texture::~Texture()
{
    DEBUG_SINGLETON_ASSERT_USAGE(Engine::Core::ResourceManager, "Engine::Resources::Texture");

    Free();
}

std::string Texture::GetFilePath() const
{
    return m_FilePath;
}

glm::uvec2 Texture::GetResolution() const
{
    return m_Resolution;
}

bool Texture::HasTransparency() const
{
    return m_HasTransparency;
}

void Texture::Load(const TextureParameters& parameters)
{
    int width, height, channels;
    unsigned char* data = stbi_load(m_FilePath.c_str(), &width, &height, &channels, 0);
    if (!data)
    {
        throw Exceptions::Common::FileNotFoundException(m_FilePath);
    }

    m_HasTransparency = channels == 4;

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

void Texture::Bind(const int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
}
