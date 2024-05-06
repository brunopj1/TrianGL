#include "AssetManager.h"

#include "soloud.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Exceptions/Core/FailedToInitializeEngineException.h"
#include "Assets/Material.h"
#include "Assets/Audio.h"
#include "Assets/Texture.h"
#include "Util/Asserts/ApplicationAsserts.h"
#include <ranges>
#include <thread>

using namespace TGL;

void AssetManager::Init()
{
    s_CanCreateAndDestroyObjects = true;

    stbi_set_flip_vertically_on_load(true);

    s_SoloudEngine = new SoLoud::Soloud();
    const SoLoud::result result = s_SoloudEngine->init();
    if (result != SoLoud::SO_NO_ERROR)
    {
        throw FailedToInitializeEngineException("Failed to init SoLoud");
    }

    s_SoloudEngine->setGlobalVolume(0.1f);
}

void AssetManager::Terminate()
{
    s_CanCreateAndDestroyObjects = false;

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

SharedPtr<TextureSlice> AssetManager::CreateTextureSlice(SharedPtr<Texture> texture, const int index)
{
    // No need to assert here since this doesn't interact with OpenGL

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
