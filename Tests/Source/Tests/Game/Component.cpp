#include "Game/Component.h"

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

	class TestComponent final : public Component
	{
	public:
		TestComponent()
			: Component(false) {}
	};
}

// Tests

BEGIN_GAME_TEST(Component, GetParent)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();

		const TestComponent* component = entity->AttachComponent<TestComponent>();

		EXPECT_TRUE(component->GetParent() == entity);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Component, Detach)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();

		TestComponent* component = entity->AttachComponent<TestComponent>();

		EXPECT_EQ(entity->FindComponent<TestComponent>(), component);

		component->Detach();

		EXPECT_EQ(entity->FindComponent<TestComponent>(), nullptr);

		EndTest();
	}
}
END_GAME_TEST()
