#pragma once
#include <string>
#include <vector>

#include "Resources/ShaderHelpers.h"
#include "Util/Macros/SingletonMacros.hpp"
#include <unordered_map>

// Forward declarations
namespace Engine::Resources::Internal
{
    class ManagedResource;
}

namespace Engine::Resources
{
    class Material;
    class Texture;
    class Shader;
}

namespace Engine::Core
{
    class ResourceManager
    {
    private:
        friend class Application;
        friend class Resources::Material;
        friend class Resources::Texture;

    private:
        inline static ResourceManager* s_Instance = nullptr;

    private:
        std::vector<Resources::Internal::ManagedResource*> m_Resources;
        std::unordered_map<Resources::Shader*, unsigned int, Resources::ShaderHash, Resources::ShaderEqual> m_Shaders;

    private:
        ResourceManager();
        ~ResourceManager();

    private:
        static void AddResource(Resources::Internal::ManagedResource* resource);
        static bool RemoveResource(Resources::Internal::ManagedResource* resource);

    private:
        static Resources::Shader* LoadShader(const std::string& vertexShader, const std::string& fragmentShader, bool isFilePath);
        static void UnloadShader(Resources::Shader* shader);
    };
}
