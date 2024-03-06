#include "DefaultResourcesCollection.h"

#include "ResourceManager.h"
#include "Util/DebugFeatures.hpp"

Engine::Core::DefaultResourcesCollection::DefaultResourcesCollection()
{
    s_Instance = this;
}

Engine::Core::DefaultResourcesCollection::~DefaultResourcesCollection()
{
    s_Instance = nullptr;
}

Engine::DefaultResources::DefaultMaterial* Engine::Core::DefaultResourcesCollection::GetDefaultMaterial()
{
    DEBUG_SINGLETON_INSTANCE(s_Instance, "DefaultResourcesCollection");

    return s_Instance->m_DefaultMaterial;
}

void Engine::Core::DefaultResourcesCollection::Init()
{
    m_DefaultMaterial = ResourceManager::LoadMaterial<DefaultResources::DefaultMaterial>();
}
