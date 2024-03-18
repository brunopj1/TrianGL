#include "Material.h"

#include "MaterialAttributes.h"
#include "Internal/Shader.h"
#include "Core/ResourceManager.h"
#include "Entities/Camera.h"

using namespace TGL;

Material::Material(const std::string& vertexShader, const std::string& fragmentShader, const bool isFilePath)
{
    ASSERT_SPAWNER_USAGE_CONSTRUCTOR(TGL::Material);

    m_Shader = ResourceManager::LoadShader(vertexShader, fragmentShader, isFilePath);

    CreateEngineAttributes();
}

Material::~Material()
{
    ResourceManager::UnloadShader(m_Shader);

    for (const auto attribute : m_Attributes)
    {
        PREPARE_SPAWNER_USAGE(TGL::MaterialAttribute);

        delete attribute;
    }
}

void Material::OnRenderSetup() const
{}

// TODO try to use the same template specialization for this implementation
TextureMaterialAttribute* Material::AddTextureAttribute(const std::string& name, const bool createIfInvalid)
{
    const int samplerLocation = m_Shader->GetUniformLocation(name);
    const int matrixLocation = m_Shader->GetUniformLocation(name + "Matrix");

    if (samplerLocation == -1 && matrixLocation == -1 && !createIfInvalid)
    {
        return nullptr;
    }

    PREPARE_SPAWNER_USAGE(TGL::MaterialAttribute);

    TextureMaterialAttribute* attribute = new TextureMaterialAttribute(samplerLocation, matrixLocation, samplerLocation != -1 ? m_NextTextureSlot++ : 255);

    if (samplerLocation != -1 || matrixLocation != -1)
    {
        m_Attributes.push_back(attribute);
    }

    return attribute;
}

void Material::Use(const glm::mat4& modelMatrix) const
{
    m_Shader->Use();

    UpdateEngineAttributes(modelMatrix);

    OnRenderSetup();

    for (const auto attribute : m_Attributes)
    {
        attribute->Bind();
    }
}

void Material::CreateEngineAttributes()
{
    m_PvmMatrix = AddAttribute<Mat4MaterialAttribute>("uPVMMatrix", false);
    m_ModelMatrix = AddAttribute<Mat4MaterialAttribute>("uModelMatrix", false);
}

void Material::UpdateEngineAttributes(const glm::mat4& modelMatrix) const
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
