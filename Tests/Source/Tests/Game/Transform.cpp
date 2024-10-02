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
}

// Tests

BEGIN_GAME_TEST(Transform, Position)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		Transform& transform = entity->GetTransform();

		transform.SetPosition({123.0f, 456.0f});
		EXPECT_EQ(transform.GetPosition().x, 123.0f);
		EXPECT_EQ(transform.GetPosition().y, 456.0f);

		transform.TranslateBy({-123.0f, -456.0f});
		EXPECT_NEAR(transform.GetPosition().x, 0.0f, 0.0001f);
		EXPECT_NEAR(transform.GetPosition().y, 0.0f, 0.0001f);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Transform, Rotation)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		Transform& transform = entity->GetTransform();

		transform.SetRotationDeg(90.0f);
		EXPECT_NEAR(transform.GetRotationDeg(), 90.0f, 0.0001f);
		EXPECT_NEAR(transform.GetRotationRad(), glm::radians(90.0f), 0.0001f);

		transform.SetRotationRad(glm::radians(180.0f));
		EXPECT_NEAR(transform.GetRotationDeg(), 180.0f, 0.0001f);
		EXPECT_NEAR(transform.GetRotationRad(), glm::radians(180.0f), 0.0001f);

		transform.RotateByDeg(-45.0f);
		EXPECT_NEAR(transform.GetRotationDeg(), 135.0f, 0.0001f);
		EXPECT_NEAR(transform.GetRotationRad(), glm::radians(135.0f), 0.0001f);

		transform.RotateByRad(glm::radians(-90.0f));
		EXPECT_NEAR(transform.GetRotationDeg(), 45.0f, 0.0001f);
		EXPECT_NEAR(transform.GetRotationRad(), glm::radians(45.0f), 0.0001f);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Transform, Scale)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		Transform& transform = entity->GetTransform();

		transform.SetScale({2.0f, 3.0f});
		EXPECT_NEAR(transform.GetScale().x, 2.0f, 0.0001f);
		EXPECT_NEAR(transform.GetScale().y, 3.0f, 0.0001f);

		transform.SetScale(4.0f);
		EXPECT_NEAR(transform.GetScale().x, 4.0f, 0.0001f);
		EXPECT_NEAR(transform.GetScale().y, 4.0f, 0.0001f);

		transform.ScaleBy({0.5f, 0.25f});
		EXPECT_NEAR(transform.GetScale().x, 2.0f, 0.0001f);
		EXPECT_NEAR(transform.GetScale().y, 1.0f, 0.0001f);

		transform.ScaleBy(0.5f);
		EXPECT_NEAR(transform.GetScale().x, 1.0f, 0.0001f);
		EXPECT_NEAR(transform.GetScale().y, 0.5f, 0.0001f);

		EndTest();
	}
}
END_GAME_TEST()
