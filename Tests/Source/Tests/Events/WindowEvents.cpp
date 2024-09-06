#include "Events/WindowEvents.h"

#include "Util/GameTestAbstractions.h"

using namespace TGL;

BEGIN_GAME_TEST(WindowEvents, WindowMovedEvent)
{
	class WindowMovedListener final : public Entity, public WindowMovedEvent
	{
	public:
		bool EventDetected = false;

		WindowMovedListener()
			: Entity(false) {}

		void OnWindowMoved(glm::uvec2 newPosition) override
		{
			EventDetected = true;
		}
	};

	void OnUpdate(f32 deltaTime) override
	{
		const WindowMovedListener* listener = SpawnEntity<WindowMovedListener>();

		EXPECT_FALSE(listener->EventDetected);

		Window::Get().SetPosition({100, 100});

		EXPECT_TRUE(listener->EventDetected);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(WindowEvents, WindowResizedEvent)
{
	class WindowMovedListener final : public Entity, public WindowResizedEvent
	{
	public:
		bool EventDetected = false;

		WindowMovedListener()
			: Entity(false) {}

		void OnWindowResized(glm::uvec2 newResolution) override
		{
			EventDetected = true;
		}
	};

	void OnUpdate(f32 deltaTime) override
	{
		const WindowMovedListener* listener = SpawnEntity<WindowMovedListener>();

		EXPECT_FALSE(listener->EventDetected);

		Window::Get().SetResolution({800, 800});

		EXPECT_TRUE(listener->EventDetected);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(WindowEvents, WindowFullscreenEvent)
{
	class WindowFullscreenListener final : public Entity, public WindowFullscreenEvent
	{
	public:
		bool EventDetected = false;

		WindowFullscreenListener()
			: Entity(false) {}

		void OnWindowFullscreen(bool fullscreen) override
		{
			EventDetected = true;
		}
	};

	void OnUpdate(f32 deltaTime) override
	{
		const WindowFullscreenListener* listener = SpawnEntity<WindowFullscreenListener>();

		EXPECT_FALSE(listener->EventDetected);

		Window::Get().SetFullscreen(true);

		EXPECT_TRUE(listener->EventDetected);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(WindowEvents, WindowMaximizedEvent)
{
	class WindowMaximizedListener final : public Entity, public WindowMaximizedEvent
	{
	public:
		bool EventDetected = false;

		WindowMaximizedListener()
			: Entity(false) {}

		void OnWindowMaximized() override
		{
			EventDetected = true;
		}
	};

	void OnUpdate(f32 deltaTime) override
	{
		const WindowMaximizedListener* listener = SpawnEntity<WindowMaximizedListener>();

		EXPECT_FALSE(listener->EventDetected);

		Window::Get().Maximize();

		EXPECT_TRUE(listener->EventDetected);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(WindowEvents, WindowMinimizedEvent)
{
	class WindowMinimizedListener final : public Entity, public WindowMinimizedEvent
	{
	public:
		bool EventDetected = false;

		WindowMinimizedListener()
			: Entity(false) {}

		void OnWindowMinimized() override
		{
			EventDetected = true;
		}
	};

	void OnUpdate(f32 deltaTime) override
	{
		const WindowMinimizedListener* listener = SpawnEntity<WindowMinimizedListener>();

		EXPECT_FALSE(listener->EventDetected);

		Window::Get().Minimize();

		EXPECT_TRUE(listener->EventDetected);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(WindowEvents, WindowRestoredEvent)
{
	class WindowRestoredListener final : public Entity, public WindowRestoredEvent
	{
	public:
		bool EventDetected = false;

		WindowRestoredListener()
			: Entity(false) {}

		void OnWindowRestored() override
		{
			EventDetected = true;
		}
	};

	void OnUpdate(f32 deltaTime) override
	{
		const WindowRestoredListener* listener = SpawnEntity<WindowRestoredListener>();

		Window::Get().Maximize();

		EXPECT_FALSE(listener->EventDetected);

		Window::Get().Restore();

		EXPECT_TRUE(listener->EventDetected);

		EndTest();
	}
}
END_GAME_TEST()
