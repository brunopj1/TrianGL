#pragma once

#include <Assets/Internal/Shader.h>
#include <Assets/MaterialUniforms.h>
#include <Core/AssetManager.h>
#include <Internal/Concepts/MaterialConcepts.h>
#include <Memory/SharedPtr.h>
#include <string>
#include <vector>

// Forward declarations
namespace TGL
{
    class Material
    {
    private:
        friend class AssetManager;
        friend class SpriteRenderer;

    private:
        Shader* m_Shader;
        std::vector<MaterialUniform*> m_Uniforms;
        unsigned char m_NextTextureSlot = 0;

    private:
        Mat4Uniform* m_PvmMatrix;
        Mat4Uniform* m_ProjectionMatrix;
        Mat4Uniform* m_ViewMatrix;
        Mat4Uniform* m_ModelMatrix;

    public:
        Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        virtual ~Material();

    public:
        Material(const Material&) = delete;
        Material& operator=(const Material&) = delete;
        Material(Material&&) = delete;
        Material& operator=(Material&&) = delete;

    protected:
        virtual void OnRenderSetup() const;
        
    public:
        template <typename T, typename... Args>
            requires SpawnableMaterial<T, Args...>
        static SharedPtr<T> CreateInstanceOf(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            return AssetManager::LoadMaterial<T>(std::forward<Args>(args)...);
        }

    protected:
        template <SpawnableMaterialUniform T>
        T* AddUniform(const std::string& name, const bool createIfInvalid = true)
        {
            return AssetManager::CreateMaterialUniform<T>(name, createIfInvalid, m_Shader, m_NextTextureSlot, m_Uniforms);
        }

    private:
        void Use(const glm::mat4& modelMatrix) const;

        void CreateEngineUniforms();
        void UpdateEngineUniforms(const glm::mat4& modelMatrix) const;
    };
}
