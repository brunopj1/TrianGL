#include "Core/Application.h"
#include <GameMode/ParticlePlaygroundGameMode.h>

i32 main()
{
	TGL::ApplicationConfig config;
	config.WindowTitle = "TrianGL - ParticlePlayground";
	config.Vsync = false;

	TGL::Application::Run<ParticlePlaygroundGameMode>(config);
}
