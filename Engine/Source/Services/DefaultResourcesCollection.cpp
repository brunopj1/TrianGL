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
    SINGLETON_CHECK_IF_INITIALIZED("DefaultResourcesCollection");

    return ResourceManager::LoadMaterial<DefaultResources::DefaultMaterial>();
}
