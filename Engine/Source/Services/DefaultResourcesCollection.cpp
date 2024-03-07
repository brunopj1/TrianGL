#include "DefaultResourcesCollection.h"

#include "Services/ResourceManager.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine::Services;

DefaultResourcesCollection::DefaultResourcesCollection()
{
    s_Instance = this;
}

DefaultResourcesCollection::~DefaultResourcesCollection()
{
    s_Instance = nullptr;
}

Engine::DefaultResources::DefaultMaterial* DefaultResourcesCollection::GetDefaultMaterial()
{
    DEBUG_SINGLETON_INSTANCE(s_Instance, "DefaultResourcesCollection");

    return ResourceManager::LoadMaterial<DefaultResources::DefaultMaterial>();
}
