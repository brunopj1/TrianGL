#include "Exceptions/Common/FileNotFoundException.h"
#include "Exceptions/OpenGL/OpenGlException.h"
#include "Exceptions/OpenGL/ShaderCompilationException.h"
#include "Exceptions/OpenGL/ShaderLinkingException.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

// Mock classes

namespace
{
	class MockAssetManager final : public AssetManager
	{
	public:
		Shader* LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) override
		{
			return AssetManager::LoadShader(vertexShaderPath, fragmentShaderPath);
		}

		void UnloadShader(Shader* shader) override
		{
			AssetManager::UnloadShader(shader);
		}

		u32 GetShaderCount() const
		{
			return static_cast<u32>(m_Shaders.size());
		}

		u32 GetShaderUsageCount(Shader* shader) const // NOLINT(CppParameterMayBeConstPtrOrRef)
		{
			const auto it = m_Shaders.find(shader);

			if (it != m_Shaders.end())
			{
				return it->second;
			}

			return 0;
		}
	};

	class MockRenderBackend final : public RenderBackend
	{
	public:
		static inline bool s_FailNextShaderCompile = false;
		static inline bool s_FailNextShaderLink = false;

	protected:
		bool CompileShader(u32 shaderId, const std::string& shaderSource, std::string& errorLog) override
		{
			if (s_FailNextShaderCompile)
			{
				s_FailNextShaderCompile = false;
				errorLog = "Mocked shader compilation error";
				return false;
			}

			return true;
		}

		bool LinkProgram(u32 programId, std::string& errorLog) override
		{
			if (s_FailNextShaderLink)
			{
				s_FailNextShaderLink = false;
				errorLog = "Mocked shader linking error";
				return false;
			}

			return true;
		}

		std::vector<ShaderUniformInfo> GetShaderUniforms(u32 programId) override
		{
			std::vector<ShaderUniformInfo> uniforms;

			uniforms.push_back({.Name = "uPosition",
								.Location = 1,
								.DataType = UniformDataType::F32,
								.Size = 2});

			uniforms.push_back({
				.Name = "uSize",
				.Location = 2,
				.DataType = UniformDataType::I32,
				.Size = 2,
			});

			return uniforms;
		}
	};

	void MockServiceBuilder(ServiceCollection& collection)
	{
		collection.CreateService<MockAssetManager>();
		collection.CreateService<MockRenderBackend>();
	}
}

BEGIN_GAME_TEST_MOCKED(Shader, Load, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		MockAssetManager* assetManager = dynamic_cast<MockAssetManager*>(&AssetManager::Get());
		ASSERT_NE(assetManager, nullptr);

		const std::string vertexPath = "Assets/Shaders/test.vert";
		const std::string fragmentPath = "Assets/Shaders/test.frag";

		Shader* shader = assetManager->LoadShader(vertexPath, fragmentPath);
		ASSERT_NE(shader, nullptr);
		EXPECT_EQ(assetManager->GetShaderCount(), 1);

		assetManager->UnloadShader(shader);
		EXPECT_EQ(assetManager->GetShaderCount(), 0);

		MockRenderBackend::s_FailNextShaderCompile = true;
		ASSERT_THROW(assetManager->LoadShader(vertexPath, fragmentPath), ShaderCompilationException);
		EXPECT_EQ(assetManager->GetShaderCount(), 0);

		MockRenderBackend::s_FailNextShaderLink = true;
		ASSERT_THROW(assetManager->LoadShader(vertexPath, fragmentPath), ShaderLinkingException);
		EXPECT_EQ(assetManager->GetShaderCount(), 0);

		const std::string invalidVertexPath = "Assets/Shaders/invalid.vert";
		const std::string invalidFragmentPath = "Assets/Shaders/invalid.frag";
		ASSERT_THROW(assetManager->LoadShader(invalidVertexPath, invalidFragmentPath), FileNotFoundException);
		EXPECT_EQ(assetManager->GetShaderCount(), 0);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(Shader, InstanceReused, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		MockAssetManager* assetManager = dynamic_cast<MockAssetManager*>(&AssetManager::Get());
		ASSERT_NE(assetManager, nullptr);

		const std::string vertexPath1 = "Assets/Shaders/test.vert";
		const std::string fragmentPath1 = "Assets/Shaders/test.frag";

		const std::string vertexPath2 = "Assets/Shaders/other_test.vert";
		const std::string fragmentPath2 = "Assets/Shaders/other_test.frag";

		EXPECT_EQ(assetManager->GetShaderCount(), 0);

		// NOLINTBEGIN(CppEntityAssignedButNoRead)

		Shader* shader1 = assetManager->LoadShader(vertexPath1, fragmentPath1);
		EXPECT_EQ(assetManager->GetShaderCount(), 1);
		EXPECT_EQ(assetManager->GetShaderUsageCount(shader1), 1);

		Shader* shader2 = assetManager->LoadShader(vertexPath2, fragmentPath2);
		EXPECT_EQ(assetManager->GetShaderCount(), 2);
		EXPECT_EQ(assetManager->GetShaderUsageCount(shader2), 1);
		ASSERT_NE(shader1, shader2);

		Shader* shader3 = assetManager->LoadShader(vertexPath1, fragmentPath1);
		EXPECT_EQ(assetManager->GetShaderCount(), 2);
		EXPECT_EQ(assetManager->GetShaderUsageCount(shader3), 2);
		EXPECT_EQ(shader3, shader1);

		assetManager->UnloadShader(shader1);
		EXPECT_EQ(assetManager->GetShaderCount(), 2);
		EXPECT_EQ(assetManager->GetShaderUsageCount(shader2), 1);
		EXPECT_EQ(assetManager->GetShaderUsageCount(shader3), 1);

		assetManager->UnloadShader(shader2);
		EXPECT_EQ(assetManager->GetShaderCount(), 1);
		EXPECT_EQ(assetManager->GetShaderUsageCount(shader3), 1);

		assetManager->UnloadShader(shader3);
		EXPECT_EQ(assetManager->GetShaderCount(), 0);

		// NOLINTEND(CppEntityAssignedButNoRead)

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(Shader, GetUniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		MockAssetManager* assetManager = dynamic_cast<MockAssetManager*>(&AssetManager::Get());
		ASSERT_NE(assetManager, nullptr);

		const std::string vertexPath = "Assets/Shaders/test.vert";
		const std::string fragmentPath = "Assets/Shaders/test.frag";

		const Shader* shader = assetManager->LoadShader(vertexPath, fragmentPath);
		ASSERT_NE(shader, nullptr);

		i32 uniformLocation = shader->GetUniformLocation("uPosition");
		EXPECT_EQ(uniformLocation, 1);

		uniformLocation = shader->GetUniformLocation("uSize");
		EXPECT_EQ(uniformLocation, 2);

		uniformLocation = shader->GetUniformLocation("uInvalid");
		EXPECT_EQ(uniformLocation, -1);

		EndTest();
	}
}
END_GAME_TEST()
