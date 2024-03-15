#include "ResourceManager.h"

#include "Resources/Material.h"
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
