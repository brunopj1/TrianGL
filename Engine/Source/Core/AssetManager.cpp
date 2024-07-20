﻿#include <Core/AssetManager.h>

#include <soloud.h>

#define STB_IMAGE_IMPLEMENTATION
#include "Assets/Internal/Quad.h"
#include <format>
#include <stb_image.h>

#include <Exceptions/Core/FailedToInitializeEngineException.h>
#include <Assets/Material.h>
#include <Assets/Audio.h>
#include <Assets/Texture.h>
#include <Internal/Asserts/ApplicationAsserts.h>
#include <ranges>
#include <thread>

using namespace TGL;

void AssetManager::Init()
{
    // STBI
    stbi_set_flip_vertically_on_load(true);

    // SoLoud
    s_SoloudEngine = new SoLoud::Soloud();
    const SoLoud::result result = s_SoloudEngine->init();
    if (result != SoLoud::SO_NO_ERROR)
    {
        int errorCode = static_cast<int>(result);
        throw FailedToInitializeEngineException(std::format("Failed to init SoLoud (error code: {0})", errorCode));
    }

    s_SoloudEngine->setGlobalVolume(0.1f);

    // Quad asset
    Quad::Init();
}

void AssetManager::Terminate()
{
    // Quad asset
    Quad::Terminate();
    
    // SoLoud
    s_SoloudEngine->deinit();
    delete s_SoloudEngine;
    s_SoloudEngine = nullptr;
}

SharedPtr<Texture> AssetManager::LoadTexture(const std::string& filePath, const TextureParameters& parameters)
{
    ASSERT_APPLICATION_OBJECT_CREATION();

    PREPARE_SPAWNER_ASSERT(Texture);

    Texture* instance = new Texture(filePath);

    instance->Init(parameters);

    return instance;
}

SharedPtr<TextureSlice> AssetManager::CreateTextureSlice(SharedPtr<Texture> texture, const i32 index)
{
    ASSERT_APPLICATION_OBJECT_CREATION();

    PREPARE_SPAWNER_ASSERT(TextureSlice);

    return new TextureSlice(std::move(texture), index);
}

void AssetManager::UnloadTexture(Texture* texture)
{
    ASSERT_APPLICATION_OBJECT_DESTRUCTION();

    texture->Free();
}

SharedPtr<Audio> AssetManager::LoadAudio(const std::string& filePath, const bool stream)
{
    ASSERT_APPLICATION_OBJECT_CREATION();
    
    PREPARE_SPAWNER_ASSERT(Audio);

    Audio* instance = new Audio(filePath, stream);

    instance->Init();

    return instance;
}

void AssetManager::UnloadAudio(Audio* audio)
{
    ASSERT_APPLICATION_OBJECT_DESTRUCTION();

    audio->Free();
}

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
    const auto it = s_Shaders.find(newShader);

    if (it == s_Shaders.end())
    {
        s_Shaders[newShader] = 1;
        newShader->Init();
        return newShader;
    }

    s_Shaders[it->first] = it->second + 1;
    delete newShader;
    return it->first;
}

void AssetManager::UnloadShader(Shader* shader)
{
    // No need to assert here since this is only used internally

    const auto it = s_Shaders.find(shader);

    if (it->second == 1)
    {
        it->first->Free();
        s_Shaders.erase(it);
        delete shader;
        return;
    }

    s_Shaders[shader] = it->second - 1;
}
