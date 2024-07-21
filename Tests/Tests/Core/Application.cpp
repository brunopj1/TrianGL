#include "Core/Application.h"
#include "Core/Window.h"
#include "Exceptions/Game/MissingGameModeException.h"
#include "Game/GameMode.h"

#include "gtest/gtest.h"
#include "Implementations/Entities/Camera.h"

class TestGameMode final : public TGL::GameMode
{
private:
    int m_Count = 5;
    
public:
    TestGameMode() = default;
    ~TestGameMode() override = default;

public:
    void OnStart() override
    {
        SpawnEntity<TGL::Camera>(true);
    }
    
    void OnUpdate(f32 deltaTime) override
    {
        if (m_Count-- == 0) TGL::Window::Close();
    }
};

TEST(Application, Run)
{
    TGL::ApplicationConfig config;
    config.WindowTitle = "Test";
    config.Vsync = false;

    TGL::Application app{config};
    app.SetGameMode<TestGameMode>();

    app.Run();
}

TEST(Application, NoGameMode)
{
    TGL::ApplicationConfig config;
    config.WindowTitle = "Test";
    config.Vsync = false;

    TGL::Application app{config};

    ASSERT_THROW(app.Run(), TGL::GameModeMissingException);
}
