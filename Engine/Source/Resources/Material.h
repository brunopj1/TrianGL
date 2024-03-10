#pragma once

#include "Shader.h"
#include "Core/ResourceManager.h"
#include "Internal/ManagedResource.h"
#include "Resources/MaterialAttributes.h"
#include "Util/Macros/MaterialMacros.hpp"
#include "Util/Macros/SpawnerMacros.hpp"
#include <string>
#include <vector>

// Forward declarat
namespace Engine
{
    class Material : public ManagedResource
    {
    private:
        friend class ResourceManager;
        friend class TextureRenderer;

    private:
        DECLARE_SPAWNER_USAGE_VAR();

    private:
        Shader* m_Shader;
        std::vector<MaterialAttribute*> m_Attributes;

    private:
        Mat4MaterialAttribute* m_PvmMatrix;
        Mat4MaterialAttribute* m_ModelMatrix;

    protected:
        Material(const std::string& vertexShader, const std::string& fragmentShader, bool isFilePath);
        ~Material() override;

    protected:
        virtual void OnRenderSetup() const;

    public:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(Engine::Material)>
        static T* Load(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            PREPARE_SPAWNER_USAGE();

            T* material = new T(std::forward<Args>(args)...);

            ResourceManager::AddResource(material);

            return material;
        }

        void Unload() override;

    protected:
        template <typename T, typename = ATTRIBUTE_TEMPLATE_SPAWN_CONDITION>
        T* AddAttribute(const std::string& name, const bool createIfInvalid = true)
        {
            const int location = m_Shader->GetUniformLocation(name);

            if (location == -1 && !createIfInvalid)
            {
                return nullptr;
            }

            T* attribute = new T(location);

            if (location != -1)
            {
                m_Attributes.push_back(attribute);
            }

            return attribute;
        }

        TextureMaterialAttribute* AddTextureAttribute(const std::string& name, unsigned int slot, bool createIfInvalid = true);

    private:
        void Use(const glm::mat4& modelMatrix) const;

        void CreateEngineAttributes();
        void UpdateEngineAttributes(const glm::mat4& modelMatrix) const;
    };
}
