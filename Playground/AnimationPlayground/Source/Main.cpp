#include "Core/Application.h"
#include <GameMode/AnimationPlaygroundGameMode.h>

i32 main()
{
	TGL::ApplicationConfig config;
	config.WindowTitle = "TrianGL - AnimationPlayground";
	config.Vsync = false;

	TGL::Application::Run<AnimationPlaygroundGameMode>(config);
}
