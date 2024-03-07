#include "ResourceManager.h"

#include "Resources/Material.h"
#include "Resources/Texture.h"
#include "Util/Macros/SingletonMacros.hpp"
#include <ranges>

using namespace Engine::Services;

ResourceManager::ResourceManager()
{
    s_Instance = this;
}

ResourceManager::~ResourceManager()
{
    PREPARE_SINGLETON_USAGE(true);

    for (const Resources::Internal::ManagedResource* resource : m_Resources)
    {
        delete resource;
    }

    s_Instance = nullptr;

    PREPARE_SINGLETON_USAGE(false);
}

Engine::Resources::Texture* ResourceManager::LoadTexture(std::string filePath, const Resources::TextureParameters& parameters)
{
    SINGLETON_CHECK_IF_INITIALIZED("ResourceManager");

    PREPARE_SINGLETON_USAGE(true);

    Resources::Texture* texture = new Resources::Texture(std::move(filePath), parameters);
    s_Instance->m_Resources.push_back(texture);

    PREPARE_SINGLETON_USAGE(false);

    return texture;
}

void ResourceManager::Unload(Resources::Internal::ManagedResource* resource)
{
    SINGLETON_CHECK_IF_INITIALIZED("ResourceManager");

    PREPARE_SINGLETON_USAGE(true);

    std::erase(s_Instance->m_Resources, resource);
    delete resource;

    PREPARE_SINGLETON_USAGE(false);
}

Engine::Resources::Shader* ResourceManager::LoadShader(const std::string& vertexShader, const std::string& fragmentShader, const bool isFilePath)
{
    // No need to call the DEBUG_SINGLETON_INSTANCE macro since this is used internally

    const auto newShader = new Resources::Shader(vertexShader, fragmentShader, isFilePath);
    const auto it = s_Instance->m_Shaders.find(newShader);

    if (it == s_Instance->m_Shaders.end())
    {
        s_Instance->m_Shaders[newShader] = 1;
        newShader->Load();
        return newShader;
    }

    s_Instance->m_Shaders[it->first] = it->second + 1;
    delete newShader;
    return it->first;
}

void ResourceManager::UnloadShader(Resources::Shader* shader)
{
    // No need to call the DEBUG_SINGLETON_INSTANCE macro since this is used internally

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
