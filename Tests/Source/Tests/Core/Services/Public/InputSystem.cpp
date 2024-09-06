#include "Core/Application.h"
#include "Core/Services/Public/Clock.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

// Mock classes

namespace
{
	class MockInputSystem final : public InputSystem
	{
		void PollEvents() override
		{
			const Clock& clock = Clock::Get();
			const u32 nextFrame = clock.GetFrameCount();

			if (nextFrame == 2)
			{
				KeyboardCallback(nullptr, static_cast<i32>(KeyCode::A), 0, static_cast<i32>(InputAction::Press), 0);
				MouseButtonCallback(nullptr, static_cast<i32>(MouseButton::Left), static_cast<i32>(InputAction::Press), 0);
			}

			if (nextFrame == 4)
			{
				KeyboardCallback(nullptr, static_cast<i32>(KeyCode::A), 0, static_cast<i32>(InputAction::Repeat), 0);
				MouseButtonCallback(nullptr, static_cast<i32>(MouseButton::Left), static_cast<i32>(InputAction::Release), 0);
			}

			if (nextFrame == 6)
			{
				KeyboardCallback(nullptr, static_cast<i32>(KeyCode::A), 0, static_cast<i32>(InputAction::Release), 0);
			}

			const glm::ivec2 mousePosition = GetMousePosition();
			MousePositionCallback(nullptr, mousePosition.x + 10, mousePosition.y + 10);

			MouseScrollCallback(nullptr, 0, -1);
		}
	};

	void MockServiceBuilder(ServiceCollection& collection)
	{
		collection.CreateService<MockInputSystem>();
	}
}

// Tests

BEGIN_GAME_TEST_MOCKED(InputSystem, Keyboard, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const InputSystem& inputSystem = InputSystem::Get();

		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			EXPECT_FALSE(inputSystem.IsKeyDown(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyPressed(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyRepeated(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyReleased(KeyCode::A));
		}
		if (frame == 2)
		{
			EXPECT_TRUE(inputSystem.IsKeyDown(KeyCode::A));
			EXPECT_TRUE(inputSystem.WasKeyPressed(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyRepeated(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyReleased(KeyCode::A));
		}
		if (frame == 3)
		{
			EXPECT_TRUE(inputSystem.IsKeyDown(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyPressed(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyRepeated(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyReleased(KeyCode::A));
		}
		if (frame == 4)
		{
			EXPECT_TRUE(inputSystem.IsKeyDown(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyPressed(KeyCode::A));
			EXPECT_TRUE(inputSystem.WasKeyRepeated(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyReleased(KeyCode::A));
		}
		if (frame == 5)
		{
			EXPECT_TRUE(inputSystem.IsKeyDown(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyPressed(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyRepeated(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyReleased(KeyCode::A));
		}
		if (frame == 6)
		{
			EXPECT_FALSE(inputSystem.IsKeyDown(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyPressed(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyRepeated(KeyCode::A));
			EXPECT_TRUE(inputSystem.WasKeyReleased(KeyCode::A));
		}
		if (frame == 7)
		{
			EXPECT_FALSE(inputSystem.IsKeyDown(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyPressed(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyRepeated(KeyCode::A));
			EXPECT_FALSE(inputSystem.WasKeyReleased(KeyCode::A));

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(InputSystem, MouseButton, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const InputSystem& inputSystem = InputSystem::Get();

		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			EXPECT_FALSE(inputSystem.IsMouseButtonDown(MouseButton::Left));
			EXPECT_FALSE(inputSystem.WasMouseButtonPressed(MouseButton::Left));
			EXPECT_FALSE(inputSystem.WasMouseButtonReleased(MouseButton::Left));
		}

		if (frame == 2)
		{
			EXPECT_TRUE(inputSystem.IsMouseButtonDown(MouseButton::Left));
			EXPECT_TRUE(inputSystem.WasMouseButtonPressed(MouseButton::Left));
			EXPECT_FALSE(inputSystem.WasMouseButtonReleased(MouseButton::Left));
		}

		if (frame == 3)
		{
			EXPECT_TRUE(inputSystem.IsMouseButtonDown(MouseButton::Left));
			EXPECT_FALSE(inputSystem.WasMouseButtonPressed(MouseButton::Left));
			EXPECT_FALSE(inputSystem.WasMouseButtonReleased(MouseButton::Left));
		}

		if (frame == 4)
		{
			EXPECT_FALSE(inputSystem.IsMouseButtonDown(MouseButton::Left));
			EXPECT_FALSE(inputSystem.WasMouseButtonPressed(MouseButton::Left));
			EXPECT_TRUE(inputSystem.WasMouseButtonReleased(MouseButton::Left));
		}

		if (frame == 5)
		{
			EXPECT_FALSE(inputSystem.IsMouseButtonDown(MouseButton::Left));
			EXPECT_FALSE(inputSystem.WasMouseButtonPressed(MouseButton::Left));
			EXPECT_FALSE(inputSystem.WasMouseButtonReleased(MouseButton::Left));

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(InputSystem, MousePosition, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		InputSystem& inputSystem = InputSystem::Get();

		static glm::ivec2 lastMousePosition = inputSystem.GetMousePosition();

		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame > 1)
		{
			const glm::ivec2 mousePosition = inputSystem.GetMousePosition();
			EXPECT_GT(mousePosition.x, lastMousePosition.x);
			EXPECT_GT(mousePosition.y, lastMousePosition.y);
			lastMousePosition = mousePosition;

			const glm::ivec2 mouseDelta = inputSystem.GetMouseDelta();
			EXPECT_EQ(mouseDelta.x, 10);
			EXPECT_EQ(mouseDelta.y, 10);
		}

		if (frame == 5)
		{
			inputSystem.SetMousePosition({123, 456});
			const glm::ivec2 mousePosition = inputSystem.GetMousePosition();
			EXPECT_EQ(mousePosition.x, 123);
			EXPECT_EQ(mousePosition.y, 456);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(InputSystem, MouseScroll, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const InputSystem& inputSystem = InputSystem::Get();

		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		const i32 mouseScroll = inputSystem.GetMouseScroll();
		EXPECT_EQ(mouseScroll, -1);

		if (frame == 5)
		{
			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(InputSystem, MouseMode, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		InputSystem& inputSystem = InputSystem::Get();

		inputSystem.SetMouseMode(MouseMode::Normal);
		EXPECT_EQ(inputSystem.GetMouseMode(), MouseMode::Normal);

		inputSystem.SetMouseMode(MouseMode::Hidden);
		EXPECT_EQ(inputSystem.GetMouseMode(), MouseMode::Hidden);

		inputSystem.SetMouseMode(MouseMode::Locked);
		EXPECT_EQ(inputSystem.GetMouseMode(), MouseMode::Locked);

		inputSystem.SetMouseMode(MouseMode::Confined);
		EXPECT_EQ(inputSystem.GetMouseMode(), MouseMode::Confined);

		EndTest();
	}
}
END_GAME_TEST()
