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
        DefaultResources::DefaultMaterial* m_DefaultMaterial;

    private:
        DefaultResourcesCollection();
        ~DefaultResourcesCollection();

    public:
        static Engine::DefaultResources::DefaultMaterial* GetDefaultMaterial();

    private:
        void Init();
    };
}
