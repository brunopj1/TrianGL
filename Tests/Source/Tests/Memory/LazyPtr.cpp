#include "Memory/LazyPtr.h"

#include "Game/Component.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

// Helper classes

namespace
{
	class TestEntity : public Entity
	{
	public:
		TestEntity()
			: Entity(false) {}
	};

	class OtherTestEntity final : public TestEntity
	{
	public:
		OtherTestEntity() = default;
	};

	class UnrelatedTestEntity final : public Entity
	{
	public:
		UnrelatedTestEntity()
			: Entity(false) {}
	};
}

// Tests

BEGIN_GAME_TEST(LazyPtr, Lifetime)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();

		LazyPtr<TestEntity> lazyPtr = entity;

		EXPECT_EQ(lazyPtr.Get(), entity);
		EXPECT_EQ(*lazyPtr, entity);

		entity->Destroy();

		EXPECT_EQ(lazyPtr.Get(), nullptr);
		EXPECT_EQ(*lazyPtr, nullptr);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(LazyPtr, ImplicitConversion)
{
	void OnUpdate(f32 deltaTime) override
	{
		OtherTestEntity* entity = SpawnEntity<OtherTestEntity>();

		LazyPtr<OtherTestEntity> lazyPtr1 = entity;
		EXPECT_EQ(lazyPtr1.Get(), entity);

		LazyPtr<TestEntity> lazyPtr2 = entity;
		EXPECT_EQ(lazyPtr2.Get(), entity);

		LazyPtr<Entity> lazyPtr3 = entity;
		EXPECT_EQ(lazyPtr3.Get(), entity);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(LazyPtr, CastTo)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<OtherTestEntity>();

		LazyPtr<TestEntity> lazyPtr1 = entity;
		EXPECT_EQ(lazyPtr1.Get(), entity);

		LazyPtr<Entity> lazyPtr2 = CastTo<Entity>(lazyPtr1);
		EXPECT_EQ(lazyPtr2.Get(), entity);

		LazyPtr<Entity> lazyPtr3 = CastTo<OtherTestEntity>(lazyPtr1);
		EXPECT_EQ(lazyPtr3.Get(), entity);

		LazyPtr<UnrelatedTestEntity> lazyPtr4 = CastTo<UnrelatedTestEntity>(lazyPtr1);
		EXPECT_EQ(lazyPtr4.Get(), nullptr);

		EndTest();
	}
}
END_GAME_TEST()
