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
		static inline i32 s_UniformSize;
		static inline UniformDataType s_UniformDataType;
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

			uniforms.push_back({.Name = "uTestUniform",
								.Location = 1,
								.DataType = s_UniformDataType,
								.Size = s_UniformSize});

			return uniforms;
		}

	protected:
		void SetUniform1i(const i32 location, const i32 value) override
		{
			RenderBackend::SetUniform1i(location, value);
			s_SetUniformCalls++;
			s_UniformDataType = UniformDataType::I32;
			s_UniformSize = 1;
		}

		void SetUniform2i(const i32 location, const glm::ivec2& value) override
		{
			RenderBackend::SetUniform2i(location, value);
			s_SetUniformCalls++;
			s_UniformDataType = UniformDataType::I32;
			s_UniformSize = 2;
		}

		void SetUniform3i(const i32 location, const glm::ivec3& value) override
		{
			RenderBackend::SetUniform3i(location, value);
			s_SetUniformCalls++;
			s_UniformDataType = UniformDataType::I32;
			s_UniformSize = 3;
		}

		void SetUniform4i(const i32 location, const glm::ivec4& value) override
		{
			RenderBackend::SetUniform4i(location, value);
			s_SetUniformCalls++;
			s_UniformDataType = UniformDataType::I32;
			s_UniformSize = 4;
		}

		void SetUniform1ui(const i32 location, const u32 value) override
		{
			RenderBackend::SetUniform1ui(location, value);
			s_SetUniformCalls++;
			s_UniformDataType = UniformDataType::U32;
			s_UniformSize = 1;
		}

		void SetUniform2ui(const i32 location, const glm::uvec2& value) override
		{
			RenderBackend::SetUniform2ui(location, value);
			s_SetUniformCalls++;
			s_UniformDataType = UniformDataType::U32;
			s_UniformSize = 2;
		}

		void SetUniform3ui(const i32 location, const glm::uvec3& value) override
		{
			RenderBackend::SetUniform3ui(location, value);
			s_SetUniformCalls++;
			s_UniformDataType = UniformDataType::U32;
			s_UniformSize = 3;
		}

		void SetUniform4ui(const i32 location, const glm::uvec4& value) override
		{
			RenderBackend::SetUniform4ui(location, value);
			s_SetUniformCalls++;
			s_UniformDataType = UniformDataType::U32;
			s_UniformSize = 4;
		}

		void SetUniform1f(const i32 location, const f32 value) override
		{
			RenderBackend::SetUniform1f(location, value);
			s_SetUniformCalls++;
			s_UniformDataType = UniformDataType::F32;
			s_UniformSize = 1;
		}

		void SetUniform2f(const i32 location, const glm::vec2& value) override
		{
			RenderBackend::SetUniform2f(location, value);
			s_SetUniformCalls++;
			s_UniformDataType = UniformDataType::F32;
			s_UniformSize = 2;
		}

		void SetUniform3f(const i32 location, const glm::vec3& value) override
		{
			RenderBackend::SetUniform3f(location, value);
			s_SetUniformCalls++;
			s_UniformDataType = UniformDataType::F32;
			s_UniformSize = 3;
		}

		void SetUniform4f(const i32 location, const glm::vec4& value) override
		{
			RenderBackend::SetUniform4f(location, value);
			s_SetUniformCalls++;
			s_UniformDataType = UniformDataType::F32;
			s_UniformSize = 4;
		}

		void SetUniformMatrix2f(const i32 location, const glm::mat2& value) override
		{
			RenderBackend::SetUniformMatrix2f(location, value);
			s_SetUniformCalls++;
			s_UniformDataType = UniformDataType::F32;
			s_UniformSize = -2;
		}

		void SetUniformMatrix3f(const i32 location, const glm::mat3& value) override
		{
			RenderBackend::SetUniformMatrix3f(location, value);
			s_SetUniformCalls++;
			s_UniformDataType = UniformDataType::F32;
			s_UniformSize = -3;
		}

		void SetUniformMatrix4f(const i32 location, const glm::mat4& value) override
		{
			RenderBackend::SetUniformMatrix4f(location, value);
			s_SetUniformCalls++;
			s_UniformDataType = UniformDataType::F32;
			s_UniformSize = -4;
		}
	};

	void MockServiceBuilder(ServiceCollection& collection)
	{
		collection.CreateService<MockRenderBackend>();
	}
}

// Helper functions

template <typename T>
T* SetupUniformTest(const UniformDataType dataType, const u32 size)
{
	Camera* _ = Entity::SpawnEntity<Camera>(true);

	TestEntity* entity = Entity::SpawnEntity<TestEntity>();
	SpriteRenderer* spriteRenderer = entity->AttachComponent<SpriteRenderer>();

	MockRenderBackend::s_UniformSize = size;
	MockRenderBackend::s_UniformDataType = dataType;

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
			IntUniform* uniform = SetupUniformTest<IntUniform>(UniformDataType::I32, 1);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = 123;
			EXPECT_EQ(uniform->Value, 123);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_UniformDataType, UniformDataType::I32);
			EXPECT_EQ(MockRenderBackend::s_UniformSize, 1);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, Int2Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			Int2Uniform* uniform = SetupUniformTest<Int2Uniform>(UniformDataType::I32, 2);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = {123, 456};
			EXPECT_EQ(uniform->Value.x, 123);
			EXPECT_EQ(uniform->Value.y, 456);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_UniformDataType, UniformDataType::I32);
			EXPECT_EQ(MockRenderBackend::s_UniformSize, 2);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, Int3Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			Int3Uniform* uniform = SetupUniformTest<Int3Uniform>(UniformDataType::I32, 3);
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
			EXPECT_EQ(MockRenderBackend::s_UniformDataType, UniformDataType::I32);
			EXPECT_EQ(MockRenderBackend::s_UniformSize, 3);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, Int4Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			Int4Uniform* uniform = SetupUniformTest<Int4Uniform>(UniformDataType::I32, 4);
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
			EXPECT_EQ(MockRenderBackend::s_UniformDataType, UniformDataType::I32);
			EXPECT_EQ(MockRenderBackend::s_UniformSize, 4);

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
			UintUniform* uniform = SetupUniformTest<UintUniform>(UniformDataType::U32, 1);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = 123;
			EXPECT_EQ(uniform->Value, 123);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_UniformDataType, UniformDataType::U32);
			EXPECT_EQ(MockRenderBackend::s_UniformSize, 1);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, Uint2Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			Uint2Uniform* uniform = SetupUniformTest<Uint2Uniform>(UniformDataType::U32, 2);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = {123, 456};
			EXPECT_EQ(uniform->Value.x, 123);
			EXPECT_EQ(uniform->Value.y, 456);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_UniformDataType, UniformDataType::U32);
			EXPECT_EQ(MockRenderBackend::s_UniformSize, 2);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, Uint3Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			Uint3Uniform* uniform = SetupUniformTest<Uint3Uniform>(UniformDataType::U32, 3);
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
			EXPECT_EQ(MockRenderBackend::s_UniformDataType, UniformDataType::U32);
			EXPECT_EQ(MockRenderBackend::s_UniformSize, 3);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, Uint4Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			Uint4Uniform* uniform = SetupUniformTest<Uint4Uniform>(UniformDataType::U32, 4);
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
			EXPECT_EQ(MockRenderBackend::s_UniformDataType, UniformDataType::U32);
			EXPECT_EQ(MockRenderBackend::s_UniformSize, 4);

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
			FloatUniform* uniform = SetupUniformTest<FloatUniform>(UniformDataType::F32, 1);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = 123.0f;
			EXPECT_EQ(uniform->Value, 123.0f);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_UniformDataType, UniformDataType::F32);
			EXPECT_EQ(MockRenderBackend::s_UniformSize, 1);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, Float2Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			Float2Uniform* uniform = SetupUniformTest<Float2Uniform>(UniformDataType::F32, 2);
			EXPECT_NE(uniform, nullptr);

			uniform->Value = {123.0f, 456.0f};
			EXPECT_EQ(uniform->Value.x, 123.0f);
			EXPECT_EQ(uniform->Value.y, 456.0f);

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_UniformDataType, UniformDataType::F32);
			EXPECT_EQ(MockRenderBackend::s_UniformSize, 2);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, Float3Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			Float3Uniform* uniform = SetupUniformTest<Float3Uniform>(UniformDataType::F32, 3);
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
			EXPECT_EQ(MockRenderBackend::s_UniformDataType, UniformDataType::F32);
			EXPECT_EQ(MockRenderBackend::s_UniformSize, 3);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(MaterialUniform, Float4Uniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			Float4Uniform* uniform = SetupUniformTest<Float4Uniform>(UniformDataType::F32, 4);
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
			EXPECT_EQ(MockRenderBackend::s_UniformDataType, UniformDataType::F32);
			EXPECT_EQ(MockRenderBackend::s_UniformSize, 4);

			EndTest();
		}
	}
}
END_GAME_TEST()

// TODO matrix uniforms

// TODO sprite uniforms (check all three locations, valid + invalid)
