#include "ResourceManager.h"

#include "Resources/Material.h"
#include "Util/Macros/SingletonMacros.hpp"
#include <ranges>

using namespace Engine::Core;

ResourceManager::ResourceManager()
{
    s_Instance = this;
}

ResourceManager::~ResourceManager()
{
    while (!m_Resources.empty())
    {
        const auto resource = *m_Resources.begin();
        resource->Unload();
    }

    s_Instance = nullptr;
}

void ResourceManager::AddResource(Resources::Internal::ManagedResource* resource)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    s_Instance->m_Resources.push_back(resource);
}

bool ResourceManager::RemoveResource(Resources::Internal::ManagedResource* resource)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return std::erase(s_Instance->m_Resources, resource) > 0;
}

Engine::Resources::Shader* ResourceManager::LoadShader(const std::string& vertexShader, const std::string& fragmentShader, const bool isFilePath)
{
    SINGLETON_CHECK_IF_INITIALIZED();

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
    SINGLETON_CHECK_IF_INITIALIZED();

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
