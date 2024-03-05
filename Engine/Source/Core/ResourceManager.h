#pragma once
#include <string>
#include <vector>

#include "Resources/TextureParameters.hpp"

// Forward declaration
namespace Engine::Resources::Internal
{
    class ManagedResource;
}

namespace Engine::Resources
{
    class Shader;
    class Texture;
}

namespace Engine::Core
{
    class ResourceManager
    {
    private:
        friend class Application;

    private:
        inline static ResourceManager* s_Instance = nullptr;

    private:
        std::vector<Resources::Internal::ManagedResource*> m_Resources;

    private:
        ResourceManager();
        ~ResourceManager();

    public:
        static Resources::Shader* LoadShader(std::string vertexShaderPath, std::string fragmentShaderPath);
        static Resources::Texture* LoadTexture(std::string filePath, const Resources::TextureParameters& parameters = {});

        static void Unload(Resources::Internal::ManagedResource* resource);
    };
}
