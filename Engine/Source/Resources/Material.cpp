#include "Material.h"

#include "MaterialUniforms.h"
#include "Internal/Shader.h"
#include "Core/ResourceManager.h"
#include "Entities/Camera.h"

using namespace TGL;

Material::Material(const std::string& vertexShader, const std::string& fragmentShader, const bool isFilePath)
{
    ASSERT_SPAWNER_USAGE_CONSTRUCTOR(TGL::Material);

    m_Shader = ResourceManager::LoadShader(vertexShader, fragmentShader, isFilePath);

    CreateEngineUniforms();
}

Material::~Material()
{
    ResourceManager::UnloadShader(m_Shader);

    for (const auto uniform : m_Uniforms)
    {
        PREPARE_SPAWNER_USAGE(TGL::MaterialUniform);

        delete uniform;
    }
}

void Material::OnRenderSetup() const
{}

// TODO try to use the same template specialization for this implementation
TextureUniform* Material::AddTextureUniform(const std::string& name, const bool createIfInvalid)
{
    const int samplerLocation = m_Shader->GetUniformLocation(name);
    const int matrixLocation = m_Shader->GetUniformLocation(name + "Matrix");
    const int resolutionLocation = m_Shader->GetUniformLocation(name + "Resolution");

    const bool isValid = samplerLocation != -1 || matrixLocation != -1 || resolutionLocation != -1;

    if (!isValid && !createIfInvalid)
    {
        return nullptr;
    }

    const unsigned char slot = samplerLocation != -1 ? m_NextTextureSlot++ : 255;

    PREPARE_SPAWNER_USAGE(TGL::MaterialUniform);

    TextureUniform* uniform = new TextureUniform(samplerLocation, matrixLocation, resolutionLocation, slot);

    if (isValid)
    {
        m_Uniforms.push_back(uniform);
    }

    return uniform;
}

void Material::Use(const glm::mat4& modelMatrix) const
{
    m_Shader->Use();

    UpdateEngineUniforms(modelMatrix);

    OnRenderSetup();

    for (const auto uniform : m_Uniforms)
    {
        uniform->Bind();
    }
}

void Material::CreateEngineUniforms()
{
    m_PvmMatrix = AddUniform<Mat4Uniform>("uPVMMatrix", false);
    m_ModelMatrix = AddUniform<Mat4Uniform>("uModelMatrix", false);
}

void Material::UpdateEngineUniforms(const glm::mat4& modelMatrix) const
{
    const Camera* camera = Camera::GetMainCamera();
    // Null checking is not needed since the game is not rendered without a camera

    if (m_PvmMatrix != nullptr)
    {
        const auto pvmMatrix = camera->GetProjectionViewMatrix() * modelMatrix;
        m_PvmMatrix->Value = pvmMatrix;
    }

    if (m_ModelMatrix != nullptr)
    {
        m_ModelMatrix->Value = modelMatrix;
    }
}
