#include "Game/Component.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

BEGIN_GAME_TEST(GameObject, Constructor)
{
	class TestEntity final : public Entity
	{
	public:
		TestEntity()
			: Entity(false) {}

		TestEntity(const bool data1)
			: Entity(false)
		{
			EXPECT_TRUE(data1);
		}

		TestEntity(const std::string& data1, const bool data2)
			: Entity(false)
		{
			EXPECT_EQ(data1, "test");
			EXPECT_TRUE(data2);
		}
	};

	class ExceptionEntity final : public Entity
	{
	public:
		ExceptionEntity(const bool shouldThrow)
			: Entity(false)
		{
			if (shouldThrow)
			{
				throw std::exception();
			}
		}
	};

	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity1 = SpawnEntity<TestEntity>();
		EXPECT_NE(entity1, nullptr);

		TestEntity* entity2 = SpawnEntity<TestEntity>(true);
		EXPECT_NE(entity2, nullptr);

		TestEntity* entity3 = SpawnEntity<TestEntity>("test", true);
		EXPECT_NE(entity3, nullptr);

		EXPECT_THROW(SpawnEntity<ExceptionEntity>(true), std::exception);

		ExceptionEntity* entity4 = SpawnEntity<ExceptionEntity>(false);
		EXPECT_NE(entity4, nullptr);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(GameObject, Id)
{
	class SingleEntity final : public Entity
	{
	public:
		SingleEntity()
			: Entity(false) {}
	};

	class NestedEntity final : public Entity
	{
	public:
		SingleEntity* ChildEntity = nullptr;

	public:
		NestedEntity()
			: Entity(false)
		{
			ChildEntity = SpawnEntity<SingleEntity>();
		}
	};

public:
	GameObject_Id_TestGameMode()
	{
		EXPECT_EQ(GetId(), 1);
	}

protected:
	void OnUpdate(f32 deltaTime) override
	{
		EXPECT_EQ(GetId(), 1);

		const SingleEntity* entity1 = SpawnEntity<SingleEntity>();
		EXPECT_EQ(entity1->GetId(), 2);

		const SingleEntity* entity2 = SpawnEntity<SingleEntity>();
		EXPECT_EQ(entity2->GetId(), 3);

		const NestedEntity* entity3 = SpawnEntity<NestedEntity>();
		EXPECT_EQ(entity3->GetId(), 4);
		EXPECT_EQ(entity3->ChildEntity->GetId(), 5);

		const SingleEntity* entity4 = SpawnEntity<SingleEntity>();
		EXPECT_EQ(entity4->GetId(), 6);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(GameObject, Start)
{
	class TestEntity final : public Entity
	{
	public:
		static inline bool s_OnStartCalled = false;

		TestEntity()
			: Entity(true) {}

		void OnStart() override
		{
			s_OnStartCalled = true;
		}
	};

	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			SpawnEntity<TestEntity>();
			EXPECT_FALSE(TestEntity::s_OnStartCalled);
		}

		if (frame == 2)
		{
			EXPECT_TRUE(TestEntity::s_OnStartCalled);
			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(GameObject, Update)
{
	class TestEntity1 final : public Entity
	{
	public:
		static inline bool s_OnUpdateCalled = false;

		TestEntity1()
			: Entity(false, -1) {}

		void OnUpdate(f32 deltaTime) override
		{
			s_OnUpdateCalled = true;
		}
	};

	class TestEntity2 final : public Entity
	{
	public:
		static inline bool s_OnUpdateCalled = false;

		TestEntity2()
			: Entity(true, -1) {}

		void OnUpdate(f32 deltaTime) override
		{
			s_OnUpdateCalled = true;
		}
	};

	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			SpawnEntity<TestEntity1>();
			SpawnEntity<TestEntity2>();

			EXPECT_FALSE(TestEntity1::s_OnUpdateCalled);
			EXPECT_FALSE(TestEntity2::s_OnUpdateCalled);
		}

		if (frame == 2)
		{
			EXPECT_FALSE(TestEntity1::s_OnUpdateCalled);
			EXPECT_TRUE(TestEntity2::s_OnUpdateCalled);
			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(GameObject, OrderOfExecution)
{
public:
	static inline bool s_TestEntityStartCalled = false;
	static inline bool s_TestEntityUpdateCalled = false;

	static inline bool s_TestComponentAStartCalled = false;
	static inline bool s_TestComponentAUpdateCalled = false;

	static inline bool s_TestComponentBStartCalled = false;
	static inline bool s_TestComponentBUpdateCalled = false;

	class TestEntity final : public Entity
	{
	public:
		TestEntity()
			: Entity(true, 0) {}

		void OnStart() override
		{
			s_TestEntityStartCalled = true;

			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestEntityStartCalled);
			EXPECT_FALSE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentAStartCalled);
			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentBStartCalled);

			EXPECT_FALSE(GameObject_OrderOfExecution_TestGameMode::s_TestEntityUpdateCalled);
			EXPECT_FALSE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentAUpdateCalled);
			EXPECT_FALSE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentBUpdateCalled);
		}

		void OnUpdate(f32 deltaTime) override
		{
			s_TestEntityUpdateCalled = true;

			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestEntityStartCalled);
			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentAStartCalled);
			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentBStartCalled);

			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestEntityUpdateCalled);
			EXPECT_FALSE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentAUpdateCalled);
			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentBUpdateCalled);
		}
	};

	class TestComponentA final : public Component
	{
	public:
		TestComponentA()
			: Component(true, 1) {}

		void OnStart() override
		{
			s_TestComponentAStartCalled = true;

			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestEntityStartCalled);
			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentAStartCalled);
			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentBStartCalled);

			EXPECT_FALSE(GameObject_OrderOfExecution_TestGameMode::s_TestEntityUpdateCalled);
			EXPECT_FALSE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentAUpdateCalled);
			EXPECT_FALSE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentBUpdateCalled);
		}

		void OnUpdate(f32 deltaTime) override
		{
			s_TestComponentAUpdateCalled = true;

			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestEntityStartCalled);
			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentAStartCalled);
			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentBStartCalled);

			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestEntityUpdateCalled);
			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentAUpdateCalled);
			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentBUpdateCalled);

			EndTest();
		}
	};

	class TestComponentB final : public Component
	{
	public:
		TestComponentB()
			: Component(true, -1) {}

		void OnStart() override
		{
			s_TestComponentBStartCalled = true;

			EXPECT_FALSE(GameObject_OrderOfExecution_TestGameMode::s_TestEntityStartCalled);
			EXPECT_FALSE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentAStartCalled);
			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentBStartCalled);

			EXPECT_FALSE(GameObject_OrderOfExecution_TestGameMode::s_TestEntityUpdateCalled);
			EXPECT_FALSE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentAUpdateCalled);
			EXPECT_FALSE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentBUpdateCalled);
		}

		void OnUpdate(f32 deltaTime) override
		{
			s_TestComponentBUpdateCalled = true;

			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestEntityStartCalled);
			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentAStartCalled);
			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentBStartCalled);

			EXPECT_FALSE(GameObject_OrderOfExecution_TestGameMode::s_TestEntityUpdateCalled);
			EXPECT_FALSE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentAUpdateCalled);
			EXPECT_TRUE(GameObject_OrderOfExecution_TestGameMode::s_TestComponentBUpdateCalled);
		}
	};

	void OnUpdate(f32 deltaTime) override
	{
		if (Clock::Get().GetFrameCount() == 1)
		{
			TestEntity* entity = SpawnEntity<TestEntity>();
			entity->AttachComponent<TestComponentA>();
			entity->AttachComponent<TestComponentB>();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(GameObject, FindEntities)
{
	class TestEntityA : public Entity
	{
	public:
		TestEntityA()
			: Entity(false) {}
	};

	class TestEntityB final : public TestEntityA
	{
	public:
		TestEntityB() = default;
	};

	void OnUpdate(f32 deltaTime) override
	{
		EXPECT_EQ(FindEntityGlobally<TestEntityA>(), nullptr);
		EXPECT_EQ(FindEntityGlobally<TestEntityB>(), nullptr);
		EXPECT_EQ(FindEntitiesGlobally<TestEntityA>().size(), 0);

		TestEntityA* entityA = SpawnEntity<TestEntityA>();
		TestEntityB* entityB = SpawnEntity<TestEntityB>();

		EXPECT_NE(FindEntityGlobally<TestEntityA>(), nullptr);
		EXPECT_EQ(FindEntityGlobally<TestEntityB>(), entityB);
		EXPECT_EQ(FindEntitiesGlobally<TestEntityA>().size(), 2);
		EXPECT_EQ(FindEntitiesGlobally<TestEntityB>().size(), 1);

		entityA->Destroy();

		EXPECT_EQ(FindEntityGlobally<TestEntityA>(), entityB);
		EXPECT_EQ(FindEntityGlobally<TestEntityB>(), entityB);
		EXPECT_EQ(FindEntitiesGlobally<TestEntityA>().size(), 1);
		EXPECT_EQ(FindEntitiesGlobally<TestEntityB>().size(), 1);

		entityB->Destroy();

		EXPECT_EQ(FindEntityGlobally<TestEntityA>(), nullptr);
		EXPECT_EQ(FindEntityGlobally<TestEntityB>(), nullptr);
		EXPECT_EQ(FindEntitiesGlobally<TestEntityA>().size(), 0);
		EXPECT_EQ(FindEntitiesGlobally<TestEntityB>().size(), 0);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(GameObject, FindComponents)
{
	class TestEntity final : public Entity
	{
	public:
		TestEntity()
			: Entity(false) {}
	};

	class TestComponentA : public Component
	{
	public:
		TestComponentA()
			: Component(false) {}
	};

	class TestComponentB final : public TestComponentA
	{
	public:
		TestComponentB() = default;
	};

	void OnUpdate(f32 deltaTime) override
	{
		EXPECT_EQ(FindComponentGlobally<TestComponentA>(), nullptr);
		EXPECT_EQ(FindComponentGlobally<TestComponentB>(), nullptr);
		EXPECT_EQ(FindComponentsGlobally<TestComponentA>().size(), 0);

		TestEntity* entity = SpawnEntity<TestEntity>();
		TestComponentA* componentA = entity->AttachComponent<TestComponentA>();
		TestComponentB* componentB = entity->AttachComponent<TestComponentB>();

		EXPECT_NE(FindComponentGlobally<TestComponentA>(), nullptr);
		EXPECT_EQ(FindComponentGlobally<TestComponentB>(), componentB);
		EXPECT_EQ(FindComponentsGlobally<TestComponentA>().size(), 2);
		EXPECT_EQ(FindComponentsGlobally<TestComponentB>().size(), 1);

		componentA->Detach();

		EXPECT_EQ(FindComponentGlobally<TestComponentA>(), componentB);
		EXPECT_EQ(FindComponentGlobally<TestComponentB>(), componentB);
		EXPECT_EQ(FindComponentsGlobally<TestComponentA>().size(), 1);
		EXPECT_EQ(FindComponentsGlobally<TestComponentB>().size(), 1);

		componentB->Detach();

		EXPECT_EQ(FindComponentGlobally<TestComponentA>(), nullptr);
		EXPECT_EQ(FindComponentGlobally<TestComponentB>(), nullptr);
		EXPECT_EQ(FindComponentsGlobally<TestComponentA>().size(), 0);
		EXPECT_EQ(FindComponentsGlobally<TestComponentB>().size(), 0);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(GameObject, CastTo)
{
	class TestEntityA : public Entity
	{
	public:
		TestEntityA()
			: Entity(false) {}
	};

	class TestEntityB final : public TestEntityA
	{
	public:
		TestEntityB() = default;
	};

	class TestEntityC final : public Entity
	{
	public:
		TestEntityC()
			: Entity(false) {}
	};

	void OnUpdate(f32 deltaTime) override
	{
		TestEntityA* entityA = SpawnEntity<TestEntityA>();
		EXPECT_EQ(CastTo<TestEntityA>(entityA), entityA);
		EXPECT_EQ(CastTo<TestEntityB>(entityA), nullptr);
		EXPECT_EQ(CastTo<TestEntityC>(entityA), nullptr);

		TestEntityB* entityB = SpawnEntity<TestEntityB>();
		EXPECT_EQ(CastTo<TestEntityA>(entityB), entityB);
		EXPECT_EQ(CastTo<TestEntityB>(entityB), entityB);
		EXPECT_EQ(CastTo<TestEntityC>(entityB), nullptr);

		TestEntityC* entityC = SpawnEntity<TestEntityC>();
		EXPECT_EQ(CastTo<TestEntityA>(entityC), nullptr);
		EXPECT_EQ(CastTo<TestEntityB>(entityC), nullptr);
		EXPECT_EQ(CastTo<TestEntityC>(entityC), entityC);

		EndTest();
	}
}
END_GAME_TEST()
