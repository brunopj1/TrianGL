#include "ResourceManager.h"

#include "soloud.h"

#define STB_IMAGE_IMPLEMENTATION
#include "soloud_wav.h"
#include "stb_image.h"

#include "Exceptions/Core/FailedToInitializeEngineException.h"
#include "Resources/Material.h"
#include "Resources/Sound.h"
#include "Resources/Texture.h"
#include "Util/Macros/SingletonMacros.h"
#include <ranges>
#include <thread>

using namespace TGL;

void ResourceManager::Init()
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

void ResourceManager::Terminate()
{
    s_CanCreateAndDestroyObjects = false;

    s_SoloudEngine->deinit();
    delete s_SoloudEngine;
    s_SoloudEngine = nullptr;
}

std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::string& filePath, const TextureParameters& parameters)
{
    ASSERT_SINGLETON_OBJECT_CREATION();

    PREPARE_SPAWNER_USAGE(Texture);

    std::shared_ptr<Texture> instance = std::make_shared<Texture>(filePath);

    instance->Init(parameters);

    return instance;
}

std::shared_ptr<TextureSlice> ResourceManager::CreateTextureSlice(Texture* texture, int index)
{
    // No need to assert here since this doesn't interact with OpenGL

    PREPARE_SPAWNER_USAGE(TextureSlice);

    return std::make_shared<TextureSlice>(texture->shared_from_this(), index);
}

void ResourceManager::UnloadTexture(Texture* texture)
{
    ASSERT_SINGLETON_OBJECT_DESTRUCTION();

    texture->Free();
}

std::shared_ptr<Sound> ResourceManager::LoadSound(const std::string& filePath)
{
    PREPARE_SPAWNER_USAGE(Sound);

    std::shared_ptr<Sound> instance = std::make_shared<Sound>(filePath);

    instance->Init();

    return instance;
}

void ResourceManager::UnloadSound(Sound* sound)
{
    ASSERT_SINGLETON_OBJECT_DESTRUCTION();

    sound->Free();
}

void ResourceManager::UnloadMaterialUniforms(const Material* material)
{
    // No need to assert here since this doesn't interact with OpenGL

    for (const auto uniform : material->m_Uniforms)
    {
        PREPARE_SPAWNER_USAGE(MaterialUniform);

        delete uniform;
    }
}

Shader* ResourceManager::LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
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

void ResourceManager::UnloadShader(Shader* shader)
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
