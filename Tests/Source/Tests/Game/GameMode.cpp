#include "Util/GameTestAbstractions.h"

using namespace TGL;

BEGIN_GAME_TEST(GameMode, Update)
{
	bool m_StartCalled = false;
	bool m_UpdateCalled = false;

	bool m_EarlyUpdateCalled = false;
	bool m_LateUpdateCalled = false;

	void OnStart() override
	{
		TestGameMode::OnStart();

		EXPECT_FALSE(m_StartCalled);

		m_StartCalled = true;

		EXPECT_TRUE(m_StartCalled);
		EXPECT_FALSE(m_UpdateCalled);
		EXPECT_FALSE(m_EarlyUpdateCalled);
		EXPECT_FALSE(m_LateUpdateCalled);
	}

	void OnEarlyUpdate(const f32 deltaTime) override
	{
		TestGameMode::OnEarlyUpdate(deltaTime);

		EXPECT_FALSE(m_EarlyUpdateCalled);

		m_EarlyUpdateCalled = true;

		EXPECT_TRUE(m_StartCalled);
		EXPECT_FALSE(m_UpdateCalled);
		EXPECT_TRUE(m_EarlyUpdateCalled);
		EXPECT_FALSE(m_LateUpdateCalled);
	}

	void OnUpdate(const f32 deltaTime) override
	{
		TestGameMode::OnUpdate(deltaTime);

		EXPECT_FALSE(m_UpdateCalled);

		m_UpdateCalled = true;

		EXPECT_TRUE(m_StartCalled);
		EXPECT_TRUE(m_UpdateCalled);
		EXPECT_TRUE(m_EarlyUpdateCalled);
		EXPECT_FALSE(m_LateUpdateCalled);
	}

	void OnLateUpdate(const f32 deltaTime) override
	{
		TestGameMode::OnLateUpdate(deltaTime);

		EXPECT_FALSE(m_LateUpdateCalled);

		m_LateUpdateCalled = true;

		EXPECT_TRUE(m_StartCalled);
		EXPECT_TRUE(m_UpdateCalled);
		EXPECT_TRUE(m_EarlyUpdateCalled);
		EXPECT_TRUE(m_LateUpdateCalled);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(GameMode, GetInstance)
{
	void OnUpdate(const f32 deltaTime) override
	{
		TestGameMode::OnUpdate(deltaTime);

		EXPECT_EQ(GameMode::GetInstance(), this);

		EndTest();
	}
}
END_GAME_TEST()
