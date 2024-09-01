#include "Core/Application.h"
#include "Core/Window.h"
#include "Game/GameMode.h"
#include "Implementations/Entities/Camera.h"

#include "gtest/gtest.h"

using namespace TGL;

class TestGameMode final : public GameMode
{
private:
	int m_Count = 5;

public:
	TestGameMode() = default;
	~TestGameMode() override = default;

public:
	void OnStart() override
	{
		SpawnEntity<Camera>(true);
	}

	void OnUpdate(f32 deltaTime) override
	{
		if (m_Count-- == 0) Window::Get().Close();
	}
};

TEST(Application, Run)
{
	ApplicationConfig config;
	config.WindowTitle = "Test";
	config.Vsync = false;

	Application::Run<TestGameMode>(config);
}
