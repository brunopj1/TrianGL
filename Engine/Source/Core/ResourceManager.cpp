#include "ResourceManager.h"

#include "Resources/Shader.h"
#include "Resources/Texture.h"
#include "Util/DebugFeatures.hpp"

using namespace Engine::Core;
using namespace Engine::Resources;

ResourceManager::ResourceManager()
{
    s_Instance = this;
}

ResourceManager::~ResourceManager()
{
    for (const Internal::ManagedResource* resource : m_Resources)
    {
        delete resource;
    }

    s_Instance = nullptr;
}

Shader* ResourceManager::LoadShader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    DEBUG_SINGLETON(s_Instance, "ResourceManager");

    Shader* shader = new Shader(std::move(vertexShaderPath), std::move(fragmentShaderPath));
    s_Instance->m_Resources.push_back(shader);
    return shader;
}

Texture* ResourceManager::LoadTexture(std::string filePath, const TextureParameters& parameters)
{
    DEBUG_SINGLETON(s_Instance, "ResourceManager");

    Texture* texture = new Texture(std::move(filePath), parameters);
    s_Instance->m_Resources.push_back(texture);
    return texture;
}

void ResourceManager::Unload(Internal::ManagedResource* resource)
{
    DEBUG_SINGLETON(s_Instance, "ResourceManager");

    std::erase(s_Instance->m_Resources, resource);
    delete resource;
}
