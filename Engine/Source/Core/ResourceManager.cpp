#include "ResourceManager.h"

#include "Resources/Texture.h"

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

Texture* ResourceManager::LoadTexture(std::string filePath, const TextureParameters& parameters)
{
    Texture* texture = new Texture(std::move(filePath), parameters);
    s_Instance->m_Resources.push_back(texture);
    return texture;
}

void ResourceManager::Unload(Internal::ManagedResource* resource)
{
    std::erase(s_Instance->m_Resources, resource);
    delete resource;
}
