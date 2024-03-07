﻿#include "ResourceManager.h"

#include "Resources/Material.h"
#include "Resources/Texture.h"
#include "Util/DebugFeatures.hpp"
#include <ranges>

using namespace Engine::Core;

ResourceManager::ResourceManager()
{
    s_Instance = this;
}

ResourceManager::~ResourceManager()
{
    DEBUG_DO(s_IsCurrentlyInUse = true);

    for (const Resources::Internal::ManagedResource* resource : m_Resources)
    {
        delete resource;
    }

    s_Instance = nullptr;

    DEBUG_DO(s_IsCurrentlyInUse = false);
}

Engine::Resources::Texture* ResourceManager::LoadTexture(std::string filePath, const Resources::TextureParameters& parameters)
{
    DEBUG_SINGLETON_INSTANCE(s_Instance, "ResourceManager");

    DEBUG_DO(s_IsCurrentlyInUse = true);

    Resources::Texture* texture = new Resources::Texture(std::move(filePath), parameters);
    s_Instance->m_Resources.push_back(texture);

    DEBUG_DO(s_IsCurrentlyInUse = false);

    return texture;
}

void ResourceManager::Unload(Resources::Internal::ManagedResource* resource)
{
    DEBUG_SINGLETON_INSTANCE(s_Instance, "ResourceManager");

    DEBUG_DO(s_IsCurrentlyInUse = true);

    std::erase(s_Instance->m_Resources, resource);
    delete resource;

    DEBUG_DO(s_IsCurrentlyInUse = false);
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
