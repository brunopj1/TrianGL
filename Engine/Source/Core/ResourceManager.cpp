#include "ResourceManager.h"

#include "Resources/Material.h"
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
    DEBUG_DO(s_IsCurrentlyInUse = true);

    for (const Internal::ManagedResource* resource : m_Resources)
    {
        delete resource;
    }

    s_Instance = nullptr;

    DEBUG_DO(s_IsCurrentlyInUse = false);
}

Texture* ResourceManager::LoadTexture(std::string filePath, const TextureParameters& parameters)
{
    DEBUG_SINGLETON_INSTANCE(s_Instance, "ResourceManager");

    DEBUG_DO(s_IsCurrentlyInUse = true);

    Texture* texture = new Texture(std::move(filePath), parameters);
    s_Instance->m_Resources.push_back(texture);

    DEBUG_DO(s_IsCurrentlyInUse = false);

    return texture;
}

void ResourceManager::Unload(Internal::ManagedResource* resource)
{
    DEBUG_SINGLETON_INSTANCE(s_Instance, "ResourceManager");

    DEBUG_DO(s_IsCurrentlyInUse = true);

    std::erase(s_Instance->m_Resources, resource);
    delete resource;

    DEBUG_DO(s_IsCurrentlyInUse = false);
}
