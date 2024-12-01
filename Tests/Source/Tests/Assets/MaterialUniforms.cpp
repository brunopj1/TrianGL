#include "Assets/Material.h"
#include "General/Camera.h"
#include "Rendering/SpriteRenderer.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

// TODO creating 2 uniforms with the same name should fail

// Helper classes

namespace
{
	class TestEntity final : public Entity
	{
	public:
		TestEntity()
			: Entity(false) {}
	};

	class TestMaterial final : public Material
	{
	public:
		TestMaterial()
			: Material("Assets/Shaders/test.vert", "Assets/Shaders/test.frag") {}
	};
}

// Mock services

namespace
{
	class MockRenderBackend final : public RenderBackend
	{
	public:
		static inline ShaderDataType s_ShaderDataType;
		static inline u32 s_SetUniformCalls;

	public:
		MockRenderBackend()
		{
			s_SetUniformCalls = 0;
		}

	protected:
		std::vector<ShaderUniformInfo> GetShaderUniforms(u32 programId) override
		{
			std::vector<ShaderUniformInfo> uniforms;

			uniforms.emplace_back("uTestUniform", s_ShaderDataType, 1);

			return uniforms;
		}

	protected:
		void SetUniform1i(const i32 location, const i32 value) override
		{
			RenderBackend::SetUniform1i(location, value);
			s_SetUniformCalls++;
			s_ShaderDataType = ShaderDataType::INT;
		}

		void SetUniform2i(const i32 location, const glm::ivec2& value) override
		{
			RenderBackend::SetUniform2i(location, value);
			s_SetUniformCalls++;
			s_ShaderDataType = ShaderDataType::IVEC2;
		}

		void SetUniform3i(const i32 location, const glm::ivec3& value) override
		{
			RenderBackend::SetUniform3i(location, value);
			s_SetUniformCalls++;
			s_ShaderDataType = ShaderDataType::IVEC3;
		}

		void SetUniform4i(const i32 location, const glm::ivec4& value) override
		{
			RenderBackend::SetUniform4i(location, value);
			s_SetUniformCalls++;
			s_ShaderDataType = ShaderDataType::IVEC4;
		}

		void SetUniform1ui(const i32 location, const u32 value) override
		{
			RenderBackend::SetUniform1ui(location, value);
			s_SetUniformCalls++;
			s_ShaderDataType = ShaderDataType::UINT;
		}

		void SetUniform2ui(const i32 location, const glm::uvec2& value) override
		{
			RenderBackend::SetUniform2ui(location, value);
			s_SetUniformCalls++;
			s_ShaderDataType = ShaderDataType::UVEC2;
		}

		void SetUniform3ui(const i32 location, const glm::uvec3& value) override
		{
			RenderBackend::SetUniform3ui(location, value);
			s_SetUniformCalls++;
			s_ShaderDataType = ShaderDataType::UVEC3;
		}

		void SetUniform4ui(const i32 location, const glm::uvec4& value) override
		{
			RenderBackend::SetUniform4ui(location, value);
			s_SetUniformCalls++;
			s_ShaderDataType = ShaderDataType::UVEC4;
		}

		void SetUniform1f(const i32 location, const f32 value) override
		{
			RenderBackend::SetUniform1f(location, value);
			s_SetUniformCalls++;
			s_ShaderDataType = ShaderDataType::FLOAT;
		}

		void SetUniform2f(const i32 location, const glm::vec2& value) override
		{
			RenderBackend::SetUniform2f(location, value);
			s_SetUniformCalls++;
			s_ShaderDataType = ShaderDataType::FVEC2;
		}

		void SetUniform3f(const i32 location, const glm::vec3& value) override
		{
			RenderBackend::SetUniform3f(location, value);
			s_SetUniformCalls++;
			s_ShaderDataType = ShaderDataType::FVEC3;
		}

		void SetUniform4f(const i32 location, const glm::vec4& value) override
		{
			RenderBackend::SetUniform4f(location, value);
			s_SetUniformCalls++;
			s_ShaderDataType = ShaderDataType::FVEC4;
		}

		void SetUniformMatrix2f(const i32 location, const glm::mat2& value) override
		{
			RenderBackend::SetUniformMatrix2f(location, value);
			s_SetUniformCalls++;
			s_ShaderDataType = ShaderDataType::MAT2;
		}

		void SetUniformMatrix3f(const i32 location, const glm::mat3& value) override
		{
			RenderBackend::SetUniformMatrix3f(location, value);
			s_SetUniformCalls++;
			s_ShaderDataType = ShaderDataType::MAT3;
		}

		void SetUniformMatrix4f(const i32 location, const glm::mat4& value) override
		{
			RenderBackend::SetUniformMatrix4f(location, value);
			s_SetUniformCalls++;
			s_ShaderDataType = ShaderDataType::MAT4;
		}
	};

	void MockServiceBuilder(ServiceCollection& collection)
	{
		collection.CreateService<MockRenderBackend>();
	}
}

// Helper functions

template <typename T>
T* SetupUniformTest(const ShaderDataType dataType)
{
	Camera* _ = Entity::SpawnEntity<Camera>(true);

	TestEntity* entity = Entity::SpawnEntity<TestEntity>();
	SpriteRenderer* spriteRenderer = entity->AttachComponent<SpriteRenderer>();

	MockRenderBackend::s_ShaderDataType = dataType;

	SharedPtr<TestMaterial> material = Material::CreateInstanceOf<TestMaterial>();
	spriteRenderer->SetMaterial(material);

	T* uniform = material->AddUniform<T>("uTestUniform", OnInvalidUniform::Ignore);
	return uniform;
}

// Tests

BEGIN_GAME_TEST_MOCKED(MaterialUniform, IntUniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			IntUniform* uniform = SetupUniformTest<IntUniform>(ShaderDataType::INT);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = 123;
			EXPECT_EQ(uniform->Value, 123);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_ShaderDataType, ShaderDataType::INT);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, UintUniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			UintUniform* uniform = SetupUniformTest<UintUniform>(ShaderDataType::UINT);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = 123;
			EXPECT_EQ(uniform->Value, 123);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_ShaderDataType, ShaderDataType::UINT);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, FloatUniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			FloatUniform* uniform = SetupUniformTest<FloatUniform>(ShaderDataType::FLOAT);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = 123.0f;
			EXPECT_EQ(uniform->Value, 123.0f);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_ShaderDataType, ShaderDataType::FLOAT);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, IVec2Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			IVec2Uniform* uniform = SetupUniformTest<IVec2Uniform>(ShaderDataType::IVEC2);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = {123, 456};
			EXPECT_EQ(uniform->Value.x, 123);
			EXPECT_EQ(uniform->Value.y, 456);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_ShaderDataType, ShaderDataType::IVEC2);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, IVec3Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			IVec3Uniform* uniform = SetupUniformTest<IVec3Uniform>(ShaderDataType::IVEC3);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = {123, 456, 789};
			EXPECT_EQ(uniform->Value.x, 123);
			EXPECT_EQ(uniform->Value.y, 456);
			EXPECT_EQ(uniform->Value.z, 789);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_ShaderDataType, ShaderDataType::IVEC3);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, IVec4Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			IVec4Uniform* uniform = SetupUniformTest<IVec4Uniform>(ShaderDataType::IVEC4);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = {123, 456, 789, -321};
			EXPECT_EQ(uniform->Value.x, 123);
			EXPECT_EQ(uniform->Value.y, 456);
			EXPECT_EQ(uniform->Value.z, 789);
			EXPECT_EQ(uniform->Value.w, -321);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_ShaderDataType, ShaderDataType::IVEC4);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, UVec2Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			UVec2Uniform* uniform = SetupUniformTest<UVec2Uniform>(ShaderDataType::UVEC2);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = {123, 456};
			EXPECT_EQ(uniform->Value.x, 123);
			EXPECT_EQ(uniform->Value.y, 456);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_ShaderDataType, ShaderDataType::UVEC2);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, UVec3Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			UVec3Uniform* uniform = SetupUniformTest<UVec3Uniform>(ShaderDataType::UVEC3);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = {123, 456, 789};
			EXPECT_EQ(uniform->Value.x, 123);
			EXPECT_EQ(uniform->Value.y, 456);
			EXPECT_EQ(uniform->Value.z, 789);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_ShaderDataType, ShaderDataType::UVEC3);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, UVec4Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			UVec4Uniform* uniform = SetupUniformTest<UVec4Uniform>(ShaderDataType::UVEC4);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = {123, 456, 789, 321};
			EXPECT_EQ(uniform->Value.x, 123);
			EXPECT_EQ(uniform->Value.y, 456);
			EXPECT_EQ(uniform->Value.z, 789);
			EXPECT_EQ(uniform->Value.w, 321);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_ShaderDataType, ShaderDataType::UVEC4);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, FVec2Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			FVec2Uniform* uniform = SetupUniformTest<FVec2Uniform>(ShaderDataType::FVEC2);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = {123.0f, 456.0f};
			EXPECT_EQ(uniform->Value.x, 123.0f);
			EXPECT_EQ(uniform->Value.y, 456.0f);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_ShaderDataType, ShaderDataType::FVEC2);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, FVec3Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			FVec3Uniform* uniform = SetupUniformTest<FVec3Uniform>(ShaderDataType::FVEC3);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = {123.0f, 456.0f, 789.0f};
			EXPECT_EQ(uniform->Value.x, 123.0f);
			EXPECT_EQ(uniform->Value.y, 456.0f);
			EXPECT_EQ(uniform->Value.z, 789.0f);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_ShaderDataType, ShaderDataType::FVEC3);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, FVec4Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			FVec4Uniform* uniform = SetupUniformTest<FVec4Uniform>(ShaderDataType::FVEC4);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = {123, 456, 789, -321};
			EXPECT_EQ(uniform->Value.x, 123.0f);
			EXPECT_EQ(uniform->Value.y, 456.0f);
			EXPECT_EQ(uniform->Value.z, 789.0f);
			EXPECT_EQ(uniform->Value.w, -321.0f);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_ShaderDataType, ShaderDataType::FVEC4);

			EndTest();
		}
	}
}
END_GAME_TEST()

// TODO matrix uniforms

// TODO sprite uniforms (check all three locations, valid + invalid)
