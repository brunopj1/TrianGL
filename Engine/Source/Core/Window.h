#pragma once

#include <glm/vec2.hpp>

// Forward Declarations
struct GLFWwindow;

namespace Engine::Core
{
	struct WindowData
	{
		const char* m_Title;
		glm::uvec2 m_Resolution;
		bool m_Vsync;
	};

	class Window
	{
	private:
		friend class Application;
		
	private:
		GLFWwindow* m_WindowPtr = nullptr;
		WindowData m_Data;

	public:
		Window(const char* title, unsigned int width, unsigned int height, bool vsync);
		~Window() = default;

	private:
		bool Init();
		void Update();
		void Terminate();

	public:
		bool ShouldClose();

		bool IsVsync();
		void SetVsync(bool vsync);

		void SetResolution(glm::uvec2 resolution);
		glm::uvec2 GetResolution();

	private:
		GLFWwindow* GetGlfwWindow();
		WindowData* GetDataPointer();
	};
}