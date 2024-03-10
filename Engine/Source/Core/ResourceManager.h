#pragma once

#include "Resources/ShaderHelpers.h"
#include "Util/Macros/SingletonMacros.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace Engine
{
    // Forward declarations
    class ManagedResource;

    class ResourceManager
    {
    private:
        friend class Application;
        friend class Material;
        friend class Texture;

    private:
        inline static ResourceManager* s_Instance = nullptr;

    private:
        std::vector<ManagedResource*> m_Resources;
        std::unordered_map<Shader*, unsigned int, ShaderHash, ShaderEqual> m_Shaders;

    private:
        ResourceManager();
        ~ResourceManager();

    private:
        static void AddResource(ManagedResource* resource);
        static bool RemoveResource(ManagedResource* resource);

    private:
        static Shader* LoadShader(const std::string& vertexShader, const std::string& fragmentShader, bool isFilePath);
        static void UnloadShader(Shader* shader);
    };
}
