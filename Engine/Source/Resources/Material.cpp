#include "Material.h"

#include "MaterialAttributes.h"
#include "Internal/Shader.h"
#include "Core/ResourceManager.h"
#include "Entities/Camera.h"

TGL::Material::Material(const std::string& vertexShader, const std::string& fragmentShader, const bool isFilePath)
{
    ASSERT_SPAWNER_USAGE_CONSTRUCTOR(TGL::Material);

    m_Shader = ResourceManager::LoadShader(vertexShader, fragmentShader, isFilePath);

    CreateEngineAttributes();
}

TGL::Material::~Material()
{
    ASSERT_SPAWNER_USAGE_DESTRUCTOR(TGL::Material);

    ResourceManager::UnloadShader(m_Shader);

    for (const auto attribute : m_Attributes)
    {
        delete attribute;
    }
}

void TGL::Material::OnRenderSetup() const
{}

void TGL::Material::Unload()
{
    ResourceManager::RemoveResource(this);

    PREPARE_SPAWNER_USAGE();

    delete this;
}

TGL::TextureMaterialAttribute* TGL::Material::AddTextureAttribute(const std::string& name, const unsigned int slot, const bool createIfInvalid)
{
    const int location = m_Shader->GetUniformLocation(name);

    if (location == -1 && !createIfInvalid)
    {
        return nullptr;
    }

    const auto attribute = new TextureMaterialAttribute(location, slot);

    if (location != -1)
    {
        m_Attributes.push_back(attribute);
    }

    return attribute;
}

void TGL::Material::Use(const glm::mat4& modelMatrix) const
{
    m_Shader->Use();

    UpdateEngineAttributes(modelMatrix);

    for (const auto attribute : m_Attributes)
    {
        attribute->Bind();
    }
}

void TGL::Material::CreateEngineAttributes()
{
    m_PvmMatrix = AddAttribute<Mat4MaterialAttribute>("uPVMMatrix", false);
    m_ModelMatrix = AddAttribute<Mat4MaterialAttribute>("uModelMatrix", false);
}

void TGL::Material::UpdateEngineAttributes(const glm::mat4& modelMatrix) const
{
    const Camera* camera = Camera::GetMainCamera();
    // Null checking is not needed since the game is not rendered without a camera

    if (m_PvmMatrix != nullptr)
    {
        const auto pvmMatrix = camera->GetProjectionViewMatrix() * modelMatrix;
        m_PvmMatrix->SetValue(pvmMatrix);
    }

    if (m_ModelMatrix != nullptr)
    {
        m_ModelMatrix->SetValue(modelMatrix);
    }
}
