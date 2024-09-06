#include "Core/Services/Window.h"

#include "Core/Services/Clock.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

BEGIN_GAME_TEST(Window, Fullscreen)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();

		EXPECT_FALSE(window.IsFullscreen());

		window.SetFullscreen(false);
		EXPECT_FALSE(window.IsFullscreen());

		window.SetFullscreen(true);
		EXPECT_TRUE(window.IsFullscreen());

		window.SetFullscreen(true);
		EXPECT_TRUE(window.IsFullscreen());

		window.SetFullscreen(false);
		EXPECT_FALSE(window.IsFullscreen());

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Window, MaximizeAndRestore)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();

		EXPECT_FALSE(window.IsMaximized());

		window.Maximize();
		EXPECT_TRUE(window.IsMaximized());

		window.Maximize();
		EXPECT_TRUE(window.IsMaximized());

		window.Restore();
		EXPECT_FALSE(window.IsMaximized());

		window.Restore();
		EXPECT_FALSE(window.IsMaximized());

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Window, MinimizeAndRestore)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();

		EXPECT_FALSE(window.IsMinimized());

		window.Minimize();
		EXPECT_TRUE(window.IsMinimized());

		window.Minimize();
		EXPECT_TRUE(window.IsMinimized());

		window.Restore();
		EXPECT_FALSE(window.IsMinimized());

		window.Restore();
		EXPECT_FALSE(window.IsMinimized());

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Window, Title)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();

		window.SetTitle("Test1");
		EXPECT_EQ(window.GetTitle(), "Test1");

		window.SetTitle("Test2");
		EXPECT_EQ(window.GetTitle(), "Test2");

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Window, Position)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();

		window.SetPosition({100, 100});
		EXPECT_EQ(window.GetPosition(), glm::ivec2(100, 100));

		window.SetPosition({200, 200});
		EXPECT_EQ(window.GetPosition(), glm::ivec2(200, 200));

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Window, Resolution)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();

		window.SetResolution({800, 600});
		EXPECT_EQ(window.GetResolution(), glm::uvec2(800, 600));
		EXPECT_NEAR(window.GetAspectRatio(), 800.0f / 600.0f, 0.01f);

		window.SetResolution({1280, 720});
		EXPECT_EQ(window.GetResolution(), glm::uvec2(1280, 720));
		EXPECT_NEAR(window.GetAspectRatio(), 1280.0f / 720.0f, 0.01f);

		EXPECT_THROW(window.SetResolution({0, 0}), std::invalid_argument);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Window, Vsync)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();

		EXPECT_FALSE(window.IsVsync());

		window.SetVsync(false);
		EXPECT_FALSE(window.IsVsync());

		window.SetVsync(true);
		EXPECT_TRUE(window.IsVsync());

		window.SetVsync(true);
		EXPECT_TRUE(window.IsVsync());

		window.SetVsync(false);
		EXPECT_FALSE(window.IsVsync());

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Window, Close)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();

		EXPECT_FALSE(window.IsClosing());

		window.Close();
		EXPECT_TRUE(window.IsClosing());

		window.Close();
		EXPECT_TRUE(window.IsClosing());

		EndTest();
	}
}
END_GAME_TEST()
