#pragma once

#include "Resources/Internal/ShaderHelpers.h"
#include "Util/Macros/SingletonMacros.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace TGL
{
    // Forward declarations
    class IdGenerator;
    class Resource;

    template <typename T, typename C>
    class LazyPtr;

    class ResourceManager
    {
    private:
        friend class Application;
        friend class Material;
        friend class Texture;

        template <typename T, typename C>
        friend class LazyPtr;

    private:
        inline static ResourceManager* s_Instance = nullptr;

    private:
        IdGenerator* m_IdGenerator;
        std::unordered_map<uint32_t, Resource*> m_Resources;
        std::unordered_map<Shader*, unsigned int, ShaderHash, ShaderEqual> m_Shaders;

    private:
        ResourceManager(IdGenerator* idGenerator);
        ~ResourceManager();

    private:
        static void AddResource(Resource* resource);
        static Resource* GetResource(uint32_t id);
        static bool RemoveResource(const Resource* resource);

    private:
        static Shader* LoadShader(const std::string& vertexShader, const std::string& fragmentShader, bool isFilePath);
        static void UnloadShader(Shader* shader);
    };
}
