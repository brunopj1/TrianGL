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

namespace Engine::Resources
{
    // Forward declaration
    class MaterialAttribute;

    class Material : public Internal::ManagedResource
    {
    private:
        friend class Core::ResourceManager;
        friend class Components::TextureRenderer;

    private:
        Shader* m_Shader;
        std::vector<MaterialAttribute*> m_Attributes;

    private:
        Mat4MaterialAttribute* m_PvmMatrix;

    protected:
        Material(const std::string& vertexShader, const std::string& fragmentShader, bool isFilePath);
        ~Material() override;

    protected:
        virtual void OnRenderSetup() const;

    protected:
        template <typename T>
        T* AddAttribute(const std::string& name)
        {
            static_assert(!std::is_same_v<MaterialAttribute, T>, "Cannot instantiate the abstract class Engine::Resources::MaterialAttribute");
            static_assert(std::is_base_of_v<MaterialAttribute, T>, "The specified class does not derive Engine::Resources::MaterialAttribute");
            static_assert(!std::is_same_v<TextureMaterialAttribute, T>, "To create a texture attribute use the 'AddTextureAttribute' method instead");
            static_assert(std::is_constructible_v<T, int>, "The specified class does not implement a valid constructor");

            const int location = m_Shader->GetUniformLocation(name);

            T* attribute = new T(location);
            m_Attributes.push_back(attribute);
            return attribute;
        }

        TextureMaterialAttribute* AddTextureAttribute(const std::string& name, unsigned int slot);

    private:
        void Use(const glm::mat4& modelMatrix) const;

        void CreateEngineAttributes();
        void UpdateEngineAttributes(const glm::mat4& modelMatrix) const;
    };
}
