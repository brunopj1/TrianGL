#include <Assets/Internal/Shader.h>
#include <Assets/Material.h>
#include <Assets/MaterialUniforms.h>
#include <Core/Services/Private/AssetManager.h>
#include <General/Camera.h>

using namespace TGL;

Material::Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	ASSERT_ASSET_FACTORY_CONSTRUCTOR(Material);

	AssetManager& assetManager = AssetManager::Get();
	m_Shader = assetManager.LoadShader(vertexShaderPath, fragmentShaderPath);

	CreateEngineUniforms();
}

Material::~Material()
{
	ASSERT_ASSET_FACTORY_DESTRUCTOR();

	AssetManager& assetManager = AssetManager::Get();
	assetManager.UnloadMaterialUniforms(this);
	assetManager.UnloadShader(m_Shader);
}

void Material::OnRenderSetup() {}

void Material::Use(const glm::mat4& modelMatrix)
{
	m_Shader->Use();

	UpdateEngineUniforms(modelMatrix);

	OnRenderSetup();

	for (const auto uniform : m_ValidUniforms)
	{
		uniform->Bind();
	}
}

void Material::CreateEngineUniforms()
{
	m_PvmMatrix = AddUniform<Mat4Uniform>("uPVMMatrix", OnInvalidUniform::Ignore);
	m_ProjectionMatrix = AddUniform<Mat4Uniform>("uProjectionMatrix", OnInvalidUniform::Ignore);
	m_ViewMatrix = AddUniform<Mat4Uniform>("uViewMatrix", OnInvalidUniform::Ignore);
	m_ModelMatrix = AddUniform<Mat4Uniform>("uModelMatrix", OnInvalidUniform::Ignore);
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
