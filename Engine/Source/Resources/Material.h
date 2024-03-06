#pragma once

#include "Shader.h"
#include "Internal/ManagedResource.h"
#include "Resources/MaterialAttributes.h"
#include <string>
#include <vector>

// Forward declaration
namespace Engine::Core
{
    class ResourceManager;
}

// TODO ensure that these classes are only called from the respective singleton (DEBUG ONLY)
// TODO Add a bool that is set to true before creating the the instance and use the controller to check if the bool is true (two way friendship)

// TODO use the default attributes in every material if they are used in the shader (PVM matrix, etc)

namespace Engine::Resources
{
    // Forward declaration
    class MaterialAttribute;

    class Material : public Internal::ManagedResource
    {
    private:
        friend class Core::ResourceManager;
        friend class Components::TextureRenderer; // TODO remove friend class

    private:
        Shader m_Shader;
        std::vector<MaterialAttribute*> m_Attributes;

    protected:
        Material(std::string vertexShader, std::string fragmentShader, bool isFilePath);
        ~Material() override;

    protected:
        template <typename T>
        T* AddAttribute(const std::string name)
        {
            static_assert(!std::is_same_v<MaterialAttribute, T>, "Cannot instantiate the abstract class Engine::Resources::MaterialAttribute");
            static_assert(std::is_base_of_v<MaterialAttribute, T>, "The specified class does not derive Engine::Resources::MaterialAttribute");
            static_assert(std::is_constructible_v<T, int>, "The specified class does not implement a valid constructor");

            // Get the location of the attribute
            int location = m_Shader.GetUniformLocation(name);

            // TODO in debug mode give a warning if the location is -1

            T* attribute = new T(location);
            m_Attributes.push_back(attribute);
            return attribute;
        }

    private:
        void Use() const;
    };
}
