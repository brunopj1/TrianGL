#include "ResourceManager.h"

#include "IdGenerator.h"
#include "Resources/Material.h"
#include "../Util/Macros/SingletonMacros.hpp"
#include <ranges>

using namespace TGL;

ResourceManager::ResourceManager(IdGenerator* idGenerator)
    : m_IdGenerator(idGenerator)
{
    s_Instance = this;
}

ResourceManager::~ResourceManager()
{
    while (!m_Resources.empty())
    {
        const auto [_, resource] = *m_Resources.begin();
        resource->Unload();
    }

    s_Instance = nullptr;
}

void ResourceManager::AddResource(Resource* resource)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::ResourceManager);

    resource->m_Id = s_Instance->m_IdGenerator->NextId();

    s_Instance->m_Resources.emplace(resource->m_Id, resource);
}

Resource* ResourceManager::GetResource(const uint64_t id)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::ResourceManager);

    const auto it = s_Instance->m_Resources.find(id);
    if (it != s_Instance->m_Resources.end()) return it->second;
    return nullptr;
}

bool ResourceManager::RemoveResource(const Resource* resource)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::ResourceManager);

    return s_Instance->m_Resources.erase(resource->m_Id) > 0;
}

Shader* ResourceManager::LoadShader(const std::string& vertexShader, const std::string& fragmentShader, const bool isFilePath)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::ResourceManager);

    const auto newShader = new Shader(vertexShader, fragmentShader, isFilePath);
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

void ResourceManager::UnloadShader(Shader* shader)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::ResourceManager);

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
