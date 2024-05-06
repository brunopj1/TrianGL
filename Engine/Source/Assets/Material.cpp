#include <Assets/Material.h>

#include <Assets/MaterialUniforms.h>
#include <Assets/Internal/Shader.h>
#include <Core/AssetManager.h>
#include <Implementations/Entities/Camera.h>

using namespace TGL;

Material::Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    ASSERT_SPAWNER_USAGE_CONSTRUCTOR(TGL::AssetManager, Material);

    m_Shader = AssetManager::LoadShader(vertexShaderPath, fragmentShaderPath);

    CreateEngineUniforms();
}

Material::~Material()
{
    ASSERT_SPAWNER_USAGE_DESTRUCTOR(TGL::SharedPtrSpawnerUtil, Asset);

    AssetManager::UnloadMaterialUniforms(this);

    AssetManager::UnloadShader(m_Shader);
}

void Material::OnRenderSetup() const
{}

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
    m_ProjectionMatrix = AddUniform<Mat4Uniform>("uProjectionMatrix", false);
    m_ViewMatrix = AddUniform<Mat4Uniform>("uViewMatrix", false);
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

    if (m_ProjectionMatrix != nullptr)
    {
        m_ProjectionMatrix->Value = camera->GetProjectionMatrix();
    }

    if (m_ViewMatrix != nullptr)
    {
        m_ViewMatrix->Value = camera->GetViewMatrix();
    }

    if (m_ModelMatrix != nullptr)
    {
        m_ModelMatrix->Value = modelMatrix;
    }
}
