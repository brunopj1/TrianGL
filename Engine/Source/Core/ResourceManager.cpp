#include "ResourceManager.h"

#include "Resources/Material.h"
#include "Resources/Texture.h"
#include "Util/Macros/SingletonMacros.hpp"
#include <ranges>

using namespace TGL;

ResourceManager::ResourceManager()
{
    s_Instance = this;
}

ResourceManager::~ResourceManager()
{
    s_Instance = nullptr;
}

std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::string& filePath, const TextureParameters& parameters)
{
    ASSERT_SINGLETON_INITIALIZED();

    PREPARE_SPAWNER_USAGE(Texture);

    std::shared_ptr<Texture> instance = std::make_shared<Texture>(filePath);

    instance->Setup(parameters);

    return instance;
}

void ResourceManager::UnloadTexture(Texture* texture)
{
    ASSERT_SINGLETON_INITIALIZED();

    texture->Free();
}

std::shared_ptr<TextureSlice> ResourceManager::CreateTextureSlice(Texture* texture, int index)
{
    ASSERT_SINGLETON_INITIALIZED();

    PREPARE_SPAWNER_USAGE(TextureSlice);

    return std::make_shared<TextureSlice>(texture->shared_from_this(), index);
}

void ResourceManager::UnloadMaterialUniforms(const Material* material)
{
    ASSERT_SINGLETON_INITIALIZED();

    for (const auto uniform : material->m_Uniforms)
    {
        PREPARE_SPAWNER_USAGE(MaterialUniform);

        delete uniform;
    }
}

Shader* ResourceManager::LoadShader(const std::string& vertexShader, const std::string& fragmentShader, const bool isFilePath)
{
    ASSERT_SINGLETON_INITIALIZED();

    const auto newShader = new Shader(vertexShader, fragmentShader, isFilePath);
    const auto it = s_Instance->m_Shaders.find(newShader);

    if (it == s_Instance->m_Shaders.end())
    {
        s_Instance->m_Shaders[newShader] = 1;
        newShader->Setup();
        return newShader;
    }

    s_Instance->m_Shaders[it->first] = it->second + 1;
    delete newShader;
    return it->first;
}

void ResourceManager::UnloadShader(Shader* shader)
{
    ASSERT_SINGLETON_INITIALIZED();

    const auto it = s_Instance->m_Shaders.find(shader);

    if (it->second == 1)
    {
        it->first->Free();
        s_Instance->m_Shaders.erase(it);
        delete shader;
        return;
    }

    s_Instance->m_Shaders[shader] = it->second - 1;
}
