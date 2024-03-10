#pragma once
#include <string>
#include <vector>

#include "Resources/TextureParameters.hpp"
#include "Resources/ShaderHelpers.h"
#include "Util/Macros/SingletonMacros.hpp"
#include <unordered_map>

// Forward declarations
namespace Engine::Core
{
    class Application;
}

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

namespace Engine::Services
{
    class ResourceManager
    {
    private:
        friend class Core::Application;
        friend class Resources::Material;
        friend class Resources::Texture;

    private:
        inline static ResourceManager* s_Instance = nullptr;
        DECLARE_SINGLETON_USAGE_VAR();

    private:
        std::vector<Resources::Internal::ManagedResource*> m_Resources;
        std::unordered_map<Resources::Shader*, unsigned int, Resources::ShaderHash, Resources::ShaderEqual> m_Shaders;

    private:
        ResourceManager();
        ~ResourceManager();

    public:
        static Resources::Texture* LoadTexture(std::string filePath, const Resources::TextureParameters& parameters = {});

        template <typename T, typename = SINGLETON_TEMPLATE_SPAWN_CONDITION_NO_ARGS(Resources::Material)>
        static T* LoadMaterial()
        {
            SINGLETON_CHECK_IF_INITIALIZED();

            PREPARE_SINGLETON_USAGE();

            T* material = new T();
            s_Instance->m_Resources.push_back(material);

            return material;
        }

        static void Unload(Resources::Internal::ManagedResource* resource);

    private:
        static Resources::Shader* LoadShader(const std::string& vertexShader, const std::string& fragmentShader, bool isFilePath);
        static void UnloadShader(Resources::Shader* shader);
    };
}
