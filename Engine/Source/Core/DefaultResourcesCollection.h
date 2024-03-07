#pragma once
#include "DefaultResources/DefaultMaterial.h"

// Forward declaration
namespace Engine::Resources
{}

namespace Engine::Core
{
    class DefaultResourcesCollection final
    {
    private:
        friend class Application;

    private:
        inline static DefaultResourcesCollection* s_Instance = nullptr;

    private:
        DefaultResourcesCollection();
        ~DefaultResourcesCollection();

    public:
        static DefaultResources::DefaultMaterial* GetDefaultMaterial();
    };
}
