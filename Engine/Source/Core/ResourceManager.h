#pragma once
#include <string>
#include <vector>

#include "Resources/TextureParameters.hpp"
#include "Util/DebugFeatures.hpp"

// Forward declaration
namespace Engine::Resources::Internal
{
    class ManagedResource;
}

namespace Engine::Resources
{
    class Material;
    class Texture;
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
        DEBUG_SINGLETON_DECLARE_USAGE_VAR();

    private:
        std::vector<Resources::Internal::ManagedResource*> m_Resources;

    private:
        ResourceManager();
        ~ResourceManager();

    public:
        static Resources::Texture* LoadTexture(std::string filePath, const Resources::TextureParameters& parameters = {});

        template <typename T>
        static T* LoadMaterial()
        {
            DEBUG_SINGLETON_INSTANCE(s_Instance, "ResourceManager");

            static_assert(!std::is_same_v<Resources::Material, T>, "Cannot instantiate the abstract class Engine::Resources::Material");
            static_assert(std::is_base_of_v<Resources::Material, T>, "The specified class does not derive Engine::Resources::Material");
            static_assert(std::is_constructible_v<T>, "The specified class does not implement an empty constructor");

            DEBUG_DO(s_IsCurrentlyInUse = true);

            T* material = new T();
            s_Instance->m_Resources.push_back(material);

            DEBUG_DO(s_IsCurrentlyInUse = false);

            return material;
        }

        static void Unload(Resources::Internal::ManagedResource* resource);
    };
}
