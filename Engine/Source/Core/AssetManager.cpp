﻿#include <Core/AssetManager.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Internal/AudioLayer.h"

#include <Exceptions/Core/FailedToInitializeEngineException.h>
#include <Assets/Material.h>
#include <Assets/Audio.h>
#include <Assets/Texture.h>
#include <ranges>
#include <thread>
#include <format>

using namespace TGL;

void AssetManager::Init()
{
    // STBI
    stbi_set_flip_vertically_on_load(true);

    // SoLoud
    int errorCode = 0;
    m_SoloudEngine = AudioLayer::InitSoloud(errorCode);
    
    if (m_SoloudEngine == nullptr)
    {
        throw FailedToInitializeEngineException(std::format("Failed to init SoLoud (error code: {0})", errorCode));
    }

    AudioLayer::SetupSoloudSettings(m_SoloudEngine);

    // Quad asset
    InitQuad();
}

void AssetManager::Terminate()
{
    // Quad asset
    TerminateQuad();

    // SoLoud
    AudioLayer::TerminateSoloud(m_SoloudEngine);
    m_SoloudEngine = nullptr;
}

void AssetManager::InitQuad()
{
    // @formatter:off

    constexpr f32 vertices[] = {
        // Positions     // Tex Coords
        -0.5f, -0.5f,    0.0f, 0.0f,    // Bottom Left
         0.5f, -0.5f,    1.0f, 0.0f,    // Bottom Right
        -0.5f,  0.5f,    0.0f, 1.0f,    // Top Left
         0.5f,  0.5f,    1.0f, 1.0f     // Top Right
    };

    constexpr u32 indices[] = {
        0, 1, 2, // Bottom Left Triangle
        1, 3, 2  // Top Right Triangle
    };

    // @formatter:on

    RenderLayer::GenerateVertexArray(m_QuadVao);
    
    RenderLayer::GenerateBuffer(m_QuadVbo, BufferType::ArrayBuffer);
    RenderLayer::SetBufferData(m_QuadVbo, BufferType::ArrayBuffer, BufferDrawType::StaticDraw, sizeof(vertices), vertices);
    
    RenderLayer::GenerateBuffer(m_QuadEbo, BufferType::ElementArrayBuffer);
    RenderLayer::SetBufferData(m_QuadEbo, BufferType::ElementArrayBuffer, BufferDrawType::StaticDraw, sizeof(indices), indices);

    SetupQuadVertexAttributes();
    
    RenderLayer::UnbindVertexArray();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void AssetManager::SetupQuadVertexAttributes() const
{
    RenderLayer::SetVertexAttributePointer(0, 2, VertexAttributeDataType::F32, false, 4 * sizeof(f32), 0);
    RenderLayer::SetVertexAttributePointer(1, 2, VertexAttributeDataType::F32, false, 4 * sizeof(f32), 2 * sizeof(f32));
}

void AssetManager::TerminateQuad()
{
    RenderLayer::DeleteBuffer(m_QuadVbo);
    m_QuadVbo = 0;

    RenderLayer::DeleteBuffer(m_QuadEbo);
    m_QuadEbo = 0;

    RenderLayer::DeleteVertexArray(m_QuadVao);
    m_QuadVao = 0;
}

u32 AssetManager::GetQuadVao() const
{
    return m_QuadVao;
}

u32 AssetManager::GetQuadVbo() const
{
    return m_QuadVbo;
}

u32 AssetManager::GetQuadEbo() const
{
    return m_QuadEbo;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
SharedPtr<Texture> AssetManager::LoadTexture(const std::string& filePath, const TextureParameters& parameters)
{
    PREPARE_SPAWNER_ASSERT(Texture);

    Texture* instance = new Texture(filePath);

    instance->Init(parameters);

    return instance;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
SharedPtr<TextureSlice> AssetManager::CreateTextureSlice(SharedPtr<Texture> texture, const i32 index)
{
    PREPARE_SPAWNER_ASSERT(TextureSlice);

    return new TextureSlice(std::move(texture), index);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void AssetManager::UnloadTexture(Texture* texture)
{
    texture->Free();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
SharedPtr<Audio> AssetManager::LoadAudio(const std::string& filePath, const bool stream)
{
    PREPARE_SPAWNER_ASSERT(Audio);

    Audio* instance = new Audio(filePath, stream);

    instance->Init();

    return instance;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void AssetManager::UnloadAudio(Audio* audio)
{
    audio->Free();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void AssetManager::UnloadMaterialUniforms(const Material* material)
{
    // No need to assert here since this doesn't interact with OpenGL

    for (const auto uniform : material->m_Uniforms)
    {
        PREPARE_SPAWNER_ASSERT(MaterialUniform);

        delete uniform;
    }
}

Shader* AssetManager::LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    // No need to assert here since this is only used internally

    const auto newShader = new Shader(vertexShaderPath, fragmentShaderPath);
    const auto it = m_Shaders.find(newShader);

    if (it == m_Shaders.end())
    {
        m_Shaders[newShader] = 1;
        newShader->Init();
        return newShader;
    }

    m_Shaders[it->first] = it->second + 1;
    delete newShader;
    return it->first;
}

void AssetManager::UnloadShader(Shader* shader)
{
    // No need to assert here since this is only used internally

    const auto it = m_Shaders.find(shader);

    if (it->second == 1)
    {
        it->first->Free();
        m_Shaders.erase(it);
        delete shader;
        return;
    }

    m_Shaders[shader] = it->second - 1;
}
