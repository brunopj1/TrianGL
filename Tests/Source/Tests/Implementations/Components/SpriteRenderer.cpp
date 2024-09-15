#include "Implementations/Components/SpriteRenderer.h"

#include "Implementations/Entities/Camera.h"
#include "Util/GameTestAbstractions.h"
#include <algorithm>

using namespace TGL;

// Mock services

namespace
{
	class MockEntityManager final : public EntityManager
	{
	public:
		static inline Renderable* s_Renderable = nullptr;
		static inline bool s_WasRendered = false;

	protected:
		void Render() const override
		{
			EntityManager::Render();

			s_WasRendered = false;

			for (const Renderable* renderable : m_RenderQueue)
			{
				if (renderable == s_Renderable)
				{
					s_WasRendered = true;
					break;
				}
			}
		}
	};

	class MockRenderBackend final : public RenderBackend
	{
	public:
		static inline u32 s_UseProgramCalls = 0;
		static inline u32 s_DrawElementsCalls = 0;

	protected:
		void UseProgram(const u32 programId) override
		{
			RenderBackend::UseProgram(programId);
			s_UseProgramCalls++;
		}

		void DrawElements(const u32 vao, const u32 ebo, const u32 vertexCount) override
		{
			RenderBackend::DrawElements(vao, ebo, vertexCount);
			s_DrawElementsCalls++;
		}
	};

	void MockServiceBuilder(ServiceCollection& collection)
	{
		collection.CreateService<MockEntityManager>();
		collection.CreateService<MockRenderBackend>();
	}
}

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

BEGIN_GAME_TEST(SpriteRenderer, Constructor)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();

		const SpriteRenderer* spriteRenderer1 = entity->AttachComponent<SpriteRenderer>();
		EXPECT_EQ(spriteRenderer1->GetMaterial(), nullptr);

		const SharedPtr<Material> material = Material::CreateInstanceOf<TestMaterial>();
		const SpriteRenderer* spriteRenderer2 = entity->AttachComponent<SpriteRenderer>(material);
		EXPECT_EQ(spriteRenderer2->GetMaterial(), material);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(SpriteRenderer, Material)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		SpriteRenderer* spriteRenderer = entity->AttachComponent<SpriteRenderer>();
		EXPECT_EQ(spriteRenderer->GetMaterial(), nullptr);

		const SharedPtr<DefaultSpriteMaterial> defaultMaterial = spriteRenderer->UseDefaultMaterial();
		EXPECT_EQ(spriteRenderer->GetMaterial(), defaultMaterial);

		spriteRenderer->SetMaterial(nullptr);
		EXPECT_EQ(spriteRenderer->GetMaterial(), nullptr);

		const SharedPtr<Material> material = Material::CreateInstanceOf<TestMaterial>();
		spriteRenderer->SetMaterial(material);
		EXPECT_EQ(spriteRenderer->GetMaterial(), material);

		spriteRenderer->SetMaterial(nullptr);
		EXPECT_EQ(spriteRenderer->GetMaterial(), nullptr);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(SpriteRenderer, Pivot)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		SpriteRenderer* spriteRenderer = entity->AttachComponent<SpriteRenderer>();

		const glm::vec2 pivot1 = spriteRenderer->GetPivot();
		ASSERT_EQ(pivot1.x, 0.5f);
		ASSERT_EQ(pivot1.y, 0.5f);

		spriteRenderer->SetPivot({0.1f, 0.2f});
		const glm::vec2 pivot2 = spriteRenderer->GetPivot();
		ASSERT_EQ(pivot2.x, 0.1f);
		ASSERT_EQ(pivot2.y, 0.2f);

		spriteRenderer->SetPivot({-0.3f, 2.4f});
		const glm::vec2 pivot3 = spriteRenderer->GetPivot();
		ASSERT_EQ(pivot3.x, -0.3f);
		ASSERT_EQ(pivot3.y, 2.4f);

		spriteRenderer->ResetPivot();
		const glm::vec2 pivot4 = spriteRenderer->GetPivot();
		ASSERT_EQ(pivot4.x, 0.5f);
		ASSERT_EQ(pivot4.y, 0.5f);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(SpriteRenderer, Render, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			SpawnEntity<Camera>(true);

			Entity* entity = SpawnEntity<TestEntity>();
			SpriteRenderer* spriteRenderer = entity->AttachComponent<SpriteRenderer>();
			spriteRenderer->UseDefaultMaterial();

			MockEntityManager::s_Renderable = spriteRenderer;

			ASSERT_EQ(MockRenderBackend::s_UseProgramCalls, 0);
			ASSERT_EQ(MockRenderBackend::s_DrawElementsCalls, 0);
		}

		if (frame == 2)
		{
			ASSERT_TRUE(MockEntityManager::s_WasRendered);
			ASSERT_EQ(MockRenderBackend::s_UseProgramCalls, 1);
			ASSERT_EQ(MockRenderBackend::s_DrawElementsCalls, 1);

			EndTest();
		}
	}
}
END_GAME_TEST()
