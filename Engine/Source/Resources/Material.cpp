#include "Material.h"

#include "MaterialAttributes.h"
#include "Shader.h"
#include "Core/ResourceManager.h"
#include "Entities/Camera.h"
#include "Util/DebugFeatures.hpp"

Engine::Resources::Material::Material(std::string vertexShader, std::string fragmentShader, const bool isFilePath)
    : m_Shader(Shader(std::move(vertexShader), std::move(fragmentShader), isFilePath))
{
    DEBUG_SINGLETON_ASSERT_USAGE(Engine::Core::ResourceManager, "Engine::Resources::Material");

    CreateEngineAttributes();
}

Engine::Resources::Material::~Material()
{
#pragma warning(suppress: 4297) // Supress the "function assumed not to throw an exception" warning
    DEBUG_SINGLETON_ASSERT_USAGE(Engine::Core::ResourceManager, "Engine::Resources::Material");

    for (const auto attribute : m_Attributes)
    {
        delete attribute;
    }
}

void Engine::Resources::Material::OnRenderSetup() const
{}

Engine::Resources::TextureMaterialAttribute* Engine::Resources::Material::AddTextureAttribute(const std::string& name, const unsigned int slot)
{
    const int location = m_Shader.GetUniformLocation(name);

    const auto attribute = new TextureMaterialAttribute(location, slot);
    m_Attributes.push_back(attribute);
    return attribute;
}

void Engine::Resources::Material::Use(const glm::mat4& modelMatrix) const
{
    m_Shader.Use();

    UpdateEngineAttributes(modelMatrix);

    for (const auto attribute : m_Attributes)
    {
        attribute->Bind();
    }
}

void Engine::Resources::Material::CreateEngineAttributes()
{
    m_PvmMatrix = AddAttribute<Mat4MaterialAttribute>("uPVMMatrix");
}

void Engine::Resources::Material::UpdateEngineAttributes(const glm::mat4& modelMatrix) const
{
    const Entities::Camera* camera = Entities::Camera::GetMainCamera();

    const auto pvmMatrix = camera->GetProjectionViewMatrix() * modelMatrix;
    m_PvmMatrix->SetValue(pvmMatrix);
}
