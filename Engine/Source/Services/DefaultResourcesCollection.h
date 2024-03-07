#pragma once
#include "DefaultResources/DefaultMaterial.h"

// Forward declarations
namespace Engine::Core
{
    class Application;
}

namespace Engine::Services
{
    class DefaultResourcesCollection final
    {
    private:
        friend class Core::Application;

    private:
        inline static DefaultResourcesCollection* s_Instance = nullptr;

    private:
        DefaultResourcesCollection();
        ~DefaultResourcesCollection();

    public:
        static DefaultResources::DefaultMaterial* GetDefaultMaterial();
    };
}
