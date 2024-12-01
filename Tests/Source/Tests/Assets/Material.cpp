#include "Assets/Material.h"

#include "General/Camera.h"
#include "Rendering/SpriteRenderer.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

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
		static constexpr u32 default_size = 10;
		static constexpr glm::vec4 default_color = glm::vec4(0.1f, 0.2f, 0.3f, 1.0f);

		IntUniform* const m_Size;
		FVec4Uniform* const m_Color;

		u32 m_OnRenderSetupCalls = 0;

		TestMaterial(const i32 size, const glm::vec4& color)
			: Material("Assets/Shaders/test.vert", "Assets/Shaders/test.frag"),
			  m_Size(AddUniform<IntUniform>("uSize")),
			  m_Color(AddUniform<FVec4Uniform>("uColor"))
		{
			m_Size->Value = size;
			m_Color->Value = color;
		}

		TestMaterial(const i32 size)
			: TestMaterial(size, default_color)
		{}

		TestMaterial(const glm::vec4 color)
			: TestMaterial(default_size, color)
		{}

		TestMaterial()
			: TestMaterial(default_size, default_color)
		{}

		TestMaterial(const OnInvalidUniform ifInvalid)
			: Material("Assets/Shaders/test.vert", "Assets/Shaders/test.frag"),
			  m_Size(AddUniform<IntUniform>("uSize", ifInvalid)),
			  m_Color(AddUniform<FVec4Uniform>("uColor", ifInvalid))
		{}

		void OnRenderSetup() override
		{
			m_OnRenderSetupCalls++;
		}
	};

	class InvalidTestMaterial final : public Material
	{
	public:
		InvalidTestMaterial()
			: Material("Assets/Shaders/test.vert", "Assets/Shaders/test.frag") {}
	};
}

// Mock services

namespace
{
	class MockRenderBackend final : public RenderBackend
	{
	public:
		static inline bool s_MissingColorUniform = false;
		static inline bool s_MissingSizeUniform = false;

		static inline u32 s_SetUniformCalls = 0;

		std::vector<ShaderUniformInfo> GetShaderUniforms(const u32 programId) override
		{
			std::vector<ShaderUniformInfo> uniforms = RenderBackend::GetShaderUniforms(programId);

			if (s_MissingColorUniform)
			{
				std::erase_if(uniforms, [](const ShaderUniformInfo& item)
							  { return item.Name == "uColor"; });
			}

			if (s_MissingSizeUniform)
			{
				std::erase_if(uniforms, [](const ShaderUniformInfo& item)
							  { return item.Name == "uSize"; });
			}

			s_MissingColorUniform = false;
			s_MissingSizeUniform = false;

			return uniforms;
		}

		void SetUniform1i(const i32 location, const i32 value) override
		{
			RenderBackend::SetUniform1i(location, value);
			s_SetUniformCalls++;
		}

		void SetUniform2i(const i32 location, const glm::ivec2& value) override
		{
			RenderBackend::SetUniform2i(location, value);
			s_SetUniformCalls++;
		}

		void SetUniform3i(const i32 location, const glm::ivec3& value) override
		{
			RenderBackend::SetUniform3i(location, value);
			s_SetUniformCalls++;
		}

		void SetUniform4i(const i32 location, const glm::ivec4& value) override
		{
			RenderBackend::SetUniform4i(location, value);
			s_SetUniformCalls++;
		}

		void SetUniform1ui(const i32 location, const u32 value) override
		{
			RenderBackend::SetUniform1ui(location, value);
			s_SetUniformCalls++;
		}

		void SetUniform2ui(const i32 location, const glm::uvec2& value) override
		{
			RenderBackend::SetUniform2ui(location, value);
			s_SetUniformCalls++;
		}

		void SetUniform3ui(const i32 location, const glm::uvec3& value) override
		{
			RenderBackend::SetUniform3ui(location, value);
			s_SetUniformCalls++;
		}

		void SetUniform4ui(const i32 location, const glm::uvec4& value) override
		{
			RenderBackend::SetUniform4ui(location, value);
			s_SetUniformCalls++;
		}

		void SetUniform1f(const i32 location, const f32 value) override
		{
			RenderBackend::SetUniform1f(location, value);
			s_SetUniformCalls++;
		}

		void SetUniform2f(const i32 location, const glm::vec2& value) override
		{
			RenderBackend::SetUniform2f(location, value);
			s_SetUniformCalls++;
		}

		void SetUniform3f(const i32 location, const glm::vec3& value) override
		{
			RenderBackend::SetUniform3f(location, value);
			s_SetUniformCalls++;
		}

		void SetUniform4f(const i32 location, const glm::vec4& value) override
		{
			RenderBackend::SetUniform4f(location, value);
			s_SetUniformCalls++;
		}

		void SetUniformMatrix2f(const i32 location, const glm::mat2& value) override
		{
			RenderBackend::SetUniformMatrix2f(location, value);
			s_SetUniformCalls++;
		}

		void SetUniformMatrix3f(const i32 location, const glm::mat3& value) override
		{
			RenderBackend::SetUniformMatrix3f(location, value);
			s_SetUniformCalls++;
		}

		void SetUniformMatrix4f(const i32 location, const glm::mat4& value) override
		{
			RenderBackend::SetUniformMatrix4f(location, value);
			s_SetUniformCalls++;
		}
	};

	void MockServiceBuilder(ServiceCollection& collection)
	{
		collection.CreateService<MockRenderBackend>();
	}
};

// Tests

// TODO test that only the valid uniforms are being bound
// TODO test that every uniform is being deleted, even if invalid

BEGIN_GAME_TEST(Material, CreateInstanceOf)
{
	void OnUpdate(f32 deltaTime) override
	{
		const SharedPtr<TestMaterial> material1 = Material::CreateInstanceOf<TestMaterial>();
		EXPECT_NE(material1.Get(), nullptr);
		EXPECT_EQ(material1->m_Size->Value, TestMaterial::default_size);
		EXPECT_EQ(material1->m_Color->Value, TestMaterial::default_color);

		const SharedPtr<TestMaterial> material2 = Material::CreateInstanceOf<TestMaterial>(42);
		EXPECT_NE(material2.Get(), nullptr);
		EXPECT_EQ(material2->m_Size->Value, 42);
		EXPECT_EQ(material2->m_Color->Value, TestMaterial::default_color);

		const SharedPtr<TestMaterial> material3 = Material::CreateInstanceOf<TestMaterial>(glm::vec4(0.9f, 0.8f, 0.7f, 1.0f));
		EXPECT_NE(material3.Get(), nullptr);
		EXPECT_EQ(material3->m_Size->Value, TestMaterial::default_size);
		EXPECT_EQ(material3->m_Color->Value, glm::vec4(0.9f, 0.8f, 0.7f, 1.0f));

		const SharedPtr<TestMaterial> material4 = Material::CreateInstanceOf<TestMaterial>(42, glm::vec4(0.9f, 0.8f, 0.7f, 1.0f));
		EXPECT_NE(material4.Get(), nullptr);
		EXPECT_EQ(material4->m_Size->Value, 42);
		EXPECT_EQ(material4->m_Color->Value, glm::vec4(0.9f, 0.8f, 0.7f, 1.0f));

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(Material, AddUniform, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		// Valid uniforms, create if invalid
		MockRenderBackend::s_MissingColorUniform = false;
		MockRenderBackend::s_MissingSizeUniform = false;
		SharedPtr<TestMaterial> material1 = Material::CreateInstanceOf<TestMaterial>(OnInvalidUniform::Create);
		EXPECT_NE(material1.Get(), nullptr);
		EXPECT_NE(material1->m_Color, nullptr);
		EXPECT_NE(material1->m_Size, nullptr);
		material1 = nullptr;

		// Invalid color uniform, create if invalid
		MockRenderBackend::s_MissingColorUniform = true;
		MockRenderBackend::s_MissingSizeUniform = false;
		SharedPtr<TestMaterial> material2 = Material::CreateInstanceOf<TestMaterial>(OnInvalidUniform::Create);
		EXPECT_NE(material2.Get(), nullptr);
		EXPECT_NE(material2->m_Color, nullptr);
		EXPECT_NE(material2->m_Size, nullptr);
		material2 = nullptr;

		// Valid uniforms, ignore if invalid
		MockRenderBackend::s_MissingColorUniform = false;
		MockRenderBackend::s_MissingSizeUniform = false;
		SharedPtr<TestMaterial> material3 = Material::CreateInstanceOf<TestMaterial>(OnInvalidUniform::Ignore);
		EXPECT_NE(material3.Get(), nullptr);
		EXPECT_NE(material3->m_Color, nullptr);
		EXPECT_NE(material3->m_Size, nullptr);
		material3 = nullptr;

		// Invalid color uniform, ignore if invalid
		MockRenderBackend::s_MissingColorUniform = true;
		MockRenderBackend::s_MissingSizeUniform = false;
		SharedPtr<TestMaterial> material4 = Material::CreateInstanceOf<TestMaterial>(OnInvalidUniform::Ignore);
		EXPECT_NE(material4.Get(), nullptr);
		EXPECT_EQ(material4->m_Color, nullptr);
		EXPECT_NE(material4->m_Size, nullptr);
		material4 = nullptr;

		// Valid color uniform, throw if invalid
		MockRenderBackend::s_MissingColorUniform = false;
		MockRenderBackend::s_MissingSizeUniform = false;
		SharedPtr<TestMaterial> material5 = Material::CreateInstanceOf<TestMaterial>(OnInvalidUniform::Throw);
		EXPECT_NE(material5.Get(), nullptr);
		EXPECT_NE(material5->m_Color, nullptr);
		EXPECT_NE(material5->m_Size, nullptr);
		material5 = nullptr;

		// Invalid color uniform, throw if invalid
		MockRenderBackend::s_MissingColorUniform = true;
		MockRenderBackend::s_MissingSizeUniform = false;
		EXPECT_THROW(Material::CreateInstanceOf<TestMaterial>(OnInvalidUniform::Throw), std::invalid_argument);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Material, UniformValidation)
{
	void OnUpdate(f32 deltaTime) override
	{
		SharedPtr<InvalidTestMaterial> material = Material::CreateInstanceOf<InvalidTestMaterial>();

		// Unknown uniform
		const IntUniform* uniform1 = material->AddUniform<IntUniform>("uUnknown", OnInvalidUniform::Ignore);
		EXPECT_EQ(uniform1, nullptr);

		// Invalid data type
		const UintUniform* uniform2 = material->AddUniform<UintUniform>("uSize", OnInvalidUniform::Ignore);
		EXPECT_EQ(uniform2, nullptr);

		// Duplicate
		const FVec4Uniform* uniform3 = material->AddUniform<FVec4Uniform>("uColor", OnInvalidUniform::Ignore);
		const FVec4Uniform* uniform4 = material->AddUniform<FVec4Uniform>("uColor", OnInvalidUniform::Ignore);
		EXPECT_NE(uniform3, nullptr);
		EXPECT_EQ(uniform4, nullptr);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Material, OnRenderSetup)
{
	SharedPtr<TestMaterial> m_Material;

	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		static SpriteRenderer* spriteRenderer = nullptr;

		if (frame == 1)
		{
			SpawnEntity<Camera>(true);

			TestEntity* entity = SpawnEntity<TestEntity>();
			spriteRenderer = entity->AttachComponent<SpriteRenderer>();
			m_Material = Material::CreateInstanceOf<TestMaterial>();
			spriteRenderer->SetMaterial(m_Material);

			EXPECT_EQ(m_Material->m_OnRenderSetupCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(m_Material->m_OnRenderSetupCalls, 1);
			spriteRenderer->SetMaterial(nullptr);
		}

		if (frame == 3)
		{
			EXPECT_EQ(m_Material->m_OnRenderSetupCalls, 1);
			spriteRenderer->SetMaterial(m_Material);
		}

		if (frame == 4)
		{
			EXPECT_EQ(m_Material->m_OnRenderSetupCalls, 2);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(Material, SmartUniformBinding, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		static SpriteRenderer* spriteRenderer = nullptr;

		if (frame == 1)
		{
			SpawnEntity<Camera>(true);

			TestEntity* entity = SpawnEntity<TestEntity>();
			spriteRenderer = entity->AttachComponent<SpriteRenderer>();

			MockRenderBackend::s_MissingColorUniform = false;
			MockRenderBackend::s_MissingSizeUniform = false;

			spriteRenderer->SetMaterial(Material::CreateInstanceOf<TestMaterial>(OnInvalidUniform::Create));

			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 2);

			spriteRenderer->SetMaterial(nullptr);

			MockRenderBackend::s_MissingColorUniform = true;
			MockRenderBackend::s_MissingSizeUniform = false;

			spriteRenderer->SetMaterial(Material::CreateInstanceOf<TestMaterial>(OnInvalidUniform::Create));
		}

		if (frame == 3)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 3);

			spriteRenderer->SetMaterial(nullptr);

			MockRenderBackend::s_MissingColorUniform = true;
			MockRenderBackend::s_MissingSizeUniform = true;

			spriteRenderer->SetMaterial(Material::CreateInstanceOf<TestMaterial>(OnInvalidUniform::Create));
		}

		if (frame == 4)
		{
			EXPECT_EQ(MockRenderBackend::s_SetUniformCalls, 3);

			EndTest();
		}
	}
}
END_GAME_TEST()

// TODO engine uniforms (created + updated)
