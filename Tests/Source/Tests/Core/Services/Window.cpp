#include "Core/Services/Window.h"

#include "Core/Services/Clock.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

TEST_GAME_BEGIN(Window, Fullscreen)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();

		ASSERT_FALSE(window.IsFullscreen());

		window.SetFullscreen(false);
		ASSERT_FALSE(window.IsFullscreen());

		window.SetFullscreen(true);
		ASSERT_TRUE(window.IsFullscreen());

		window.SetFullscreen(true);
		ASSERT_TRUE(window.IsFullscreen());

		window.SetFullscreen(false);
		ASSERT_FALSE(window.IsFullscreen());

		window.Close();
	}
}
TEST_GAME_END()

TEST_GAME_BEGIN(Window, MaximizeAndRestore)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();

		ASSERT_FALSE(window.IsMaximized());

		window.Maximize();
		ASSERT_TRUE(window.IsMaximized());

		window.Maximize();
		ASSERT_TRUE(window.IsMaximized());

		window.Restore();
		ASSERT_FALSE(window.IsMaximized());

		window.Restore();
		ASSERT_FALSE(window.IsMaximized());

		window.Close();
	}
}
TEST_GAME_END()

TEST_GAME_BEGIN(Window, MinimizeAndRestore)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();

		ASSERT_FALSE(window.IsMinimized());

		window.Minimize();
		ASSERT_TRUE(window.IsMinimized());

		window.Minimize();
		ASSERT_TRUE(window.IsMinimized());

		window.Restore();
		ASSERT_FALSE(window.IsMinimized());

		window.Restore();
		ASSERT_FALSE(window.IsMinimized());

		window.Close();
	}
}
TEST_GAME_END()

TEST_GAME_BEGIN(Window, Title)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();

		window.SetTitle("Test1");
		ASSERT_EQ(window.GetTitle(), "Test1");

		window.SetTitle("Test2");
		ASSERT_EQ(window.GetTitle(), "Test2");

		window.Close();
	}
}
TEST_GAME_END()

TEST_GAME_BEGIN(Window, Position)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();

		window.SetPosition({100, 100});
		ASSERT_EQ(window.GetPosition(), glm::ivec2(100, 100));

		window.SetPosition({200, 200});
		ASSERT_EQ(window.GetPosition(), glm::ivec2(200, 200));

		window.Close();
	}
}
TEST_GAME_END()

TEST_GAME_BEGIN(Window, Resolution)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();
		window.Close();

		window.SetResolution({800, 600});
		ASSERT_EQ(window.GetResolution(), glm::uvec2(800, 600));
		ASSERT_NEAR(window.GetAspectRatio(), 800.0f / 600.0f, 0.01f);

		window.SetResolution({1280, 720});
		ASSERT_EQ(window.GetResolution(), glm::uvec2(1280, 720));
		ASSERT_NEAR(window.GetAspectRatio(), 1280.0f / 720.0f, 0.01f);

		ASSERT_THROW(window.SetResolution({0, 0}), std::invalid_argument);
	}
}
TEST_GAME_END()

TEST_GAME_BEGIN(Window, Vsync)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();
		window.Close();

		ASSERT_FALSE(window.IsVsync());

		window.SetVsync(false);
		ASSERT_FALSE(window.IsVsync());

		window.SetVsync(true);
		ASSERT_TRUE(window.IsVsync());

		window.SetVsync(true);
		ASSERT_TRUE(window.IsVsync());

		window.SetVsync(false);
		ASSERT_FALSE(window.IsVsync());
	}
}
TEST_GAME_END()

TEST_GAME_BEGIN(Window, Close)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();

		ASSERT_FALSE(window.IsClosing());

		window.Close();
		ASSERT_TRUE(window.IsClosing());

		window.Close();
		ASSERT_TRUE(window.IsClosing());
	}
}
TEST_GAME_END()
