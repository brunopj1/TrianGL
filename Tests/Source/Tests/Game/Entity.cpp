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

BEGIN_GAME_TEST(Entity, AttachDetachComponent)
{
	class TestComponent final : public Component
	{
	public:
		static inline bool s_Created = false;
		static inline bool s_Destroyed = false;

		TestComponent()
			: Component(false)
		{
			s_Created = true;
		}

		~TestComponent() override
		{
			s_Destroyed = true;
		}
	};

	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();

		EXPECT_FALSE(TestComponent::s_Created);
		EXPECT_FALSE(TestComponent::s_Destroyed);

		TestComponent* component = entity->AttachComponent<TestComponent>();

		EXPECT_TRUE(TestComponent::s_Created);
		EXPECT_EQ(component->GetParent(), entity);

		component->Detach();

		EXPECT_TRUE(TestComponent::s_Destroyed);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Entity, FindComponent)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();

		EXPECT_EQ(entity->FindComponent<TestComponent>(), nullptr);
		EXPECT_EQ(entity->FindComponents<TestComponent>().size(), 0);

		TestComponent* component = entity->AttachComponent<TestComponent>();

		TestComponent* foundComponent = entity->FindComponent<TestComponent>();
		EXPECT_EQ(foundComponent, component);

		const std::vector<TestComponent*> foundComponents = entity->FindComponents<TestComponent>();
		EXPECT_EQ(foundComponents.size(), 1);
		EXPECT_EQ(foundComponents[0], component);

		component->Detach();

		EXPECT_EQ(entity->FindComponent<TestComponent>(), nullptr);
		EXPECT_EQ(entity->FindComponents<TestComponent>().size(), 0);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Entity, Destroy)
{
	class TestEntity final : public Entity
	{
	public:
		static inline bool s_Destroyed = false;

		TestEntity()
			: Entity(false) {}

		~TestEntity() override
		{
			s_Destroyed = true;
		}
	};

	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();

		EXPECT_FALSE(TestEntity::s_Destroyed);

		entity->Destroy();

		EXPECT_TRUE(TestEntity::s_Destroyed);

		EndTest();
	}
};

BEGIN_GAME_TEST(Entity, Transform)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		EXPECT_NO_THROW(entity->GetTransform());

		const TestEntity* constEntity = entity;
		EXPECT_NO_THROW(constEntity->GetTransform());

		EndTest();
	}
}
END_GAME_TEST()
