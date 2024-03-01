#pragma once

#include "Core/Window.h"

namespace Engine::Core
{
	class Application
	{
	private:
		Window m_Window{"TrianGL", 1600, 900, false};

	public:
		Application() = default;
		~Application() = default;

	public:
		void Run();

	private:
		bool Init();
		void Loop();
		void Terminate();
	};
}