#include "Implementations/Components/SpriteRenderer.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

// Mock services

namespace
{
	class MockEntityManager final : public EntityManager
	{
	public:
		const std::vector<Renderable*>& GetRenderQueue() const
		{
			return m_RenderQueue;
		}
	};

	void MockServiceBuilder(ServiceCollection& collection)
	{
		collection.CreateService<MockEntityManager>();
	}
}

// Tests

BEGIN_GAME_TEST_MOCKED(Renderable, ZIndex, MockServiceBuilder)
{
	class TestEntity final : public Entity
	{
	public:
		SpriteRenderer* m_SpriteRenderer1 = nullptr;
		SpriteRenderer* m_SpriteRenderer2 = nullptr;
		SpriteRenderer* m_SpriteRenderer3 = nullptr;

		TestEntity()
			: Entity(false)
		{
			m_SpriteRenderer1 = AttachComponent<SpriteRenderer>();
			m_SpriteRenderer2 = AttachComponent<SpriteRenderer>();
			m_SpriteRenderer3 = AttachComponent<SpriteRenderer>();
		}
	};

	void OnUpdate(f32 deltaTime) override
	{
		MockEntityManager* entityManager = dynamic_cast<MockEntityManager*>(&EntityManager::Get());
		EXPECT_NE(entityManager, nullptr);

		const std::vector<Renderable*>& renderQueue = entityManager->GetRenderQueue();

		const TestEntity* entity = SpawnEntity<TestEntity>();

		EXPECT_EQ(renderQueue.size(), 3);
		for (const auto renderable : renderQueue)
		{
			EXPECT_EQ(renderable->GetZIndex(), 0);
		}

		entity->m_SpriteRenderer3->SetZIndex(1);
		EXPECT_EQ(renderQueue[2], entity->m_SpriteRenderer3);

		entity->m_SpriteRenderer1->SetZIndex(5);
		EXPECT_EQ(renderQueue[2], entity->m_SpriteRenderer1);

		entity->m_SpriteRenderer2->SetZIndex(3);
		EXPECT_EQ(renderQueue[1], entity->m_SpriteRenderer2);

		entity->m_SpriteRenderer1->SetZIndex(-77);
		EXPECT_EQ(renderQueue[0], entity->m_SpriteRenderer1);

		entity->m_SpriteRenderer3->SetZIndex(0);
		EXPECT_EQ(renderQueue[1], entity->m_SpriteRenderer3);

		entity->m_SpriteRenderer2->SetZIndex(-4);
		EXPECT_EQ(renderQueue[1], entity->m_SpriteRenderer2);

		EndTest();
	}
}
END_GAME_TEST()
