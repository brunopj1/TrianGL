#pragma once

#include "Internal/Macros/ServiceMacros.h"
#include <Core/DataTypes.h>
#include <Core/Service.h>
#include <glm/vec2.hpp>
#include <string>

// Forward declarations
struct GLFWwindow; // NOLINT(CppInconsistentNaming, IdentifierTypo)

namespace TGL
{
	class Window : public Service<Window> // NOLINT(CppClassCanBeFinal)
	{
	private:
		friend class Application;
		friend class InputLayer;

	protected:
		GLFWwindow* m_WindowPtr = nullptr;

	protected:
		std::string m_Title;

		glm::ivec2 m_Position;
		glm::uvec2 m_Resolution;
		f32 m_AspectRatio;

		bool m_Fullscreen = false;
		bool m_Maximized = false;
		bool m_Minimized = false;

		bool m_Vsync = false;

		bool m_Closing = false;

	protected:
		Window() = default;
		SERVICE_DESTRUCTOR ~Window() = default;

	public:
		SERVICE_API bool IsFullscreen() const;
		SERVICE_API void SetFullscreen(bool fullscreen);

		SERVICE_API bool IsMaximized() const;
		SERVICE_API void Maximize();

		SERVICE_API bool IsMinimized() const;
		SERVICE_API void Minimize();

		SERVICE_API void Restore();

		SERVICE_API std::string GetTitle();
		SERVICE_API void SetTitle(const std::string& title);

		SERVICE_API glm::ivec2 GetPosition() const;
		SERVICE_API void SetPosition(glm::ivec2 position);

		SERVICE_API glm::uvec2 GetResolution() const;
		SERVICE_API void SetResolution(glm::uvec2 resolution);

		SERVICE_API f32 GetAspectRatio() const;

		SERVICE_API bool IsVsync() const;
		SERVICE_API void SetVsync(bool vsync);

		SERVICE_API void Close();
		SERVICE_API bool IsClosing() const;

	protected:
		SERVICE_API GLFWwindow* Init(std::string title, glm::ivec2 position, glm::uvec2 resolution, bool fullscreen, bool vsync);
		SERVICE_API void Terminate() const;

	protected:
		SERVICE_API GLFWwindow* GetGlfwWindow() const;

	protected:
		static void CloseCallback(GLFWwindow* windowPtr);

		static void PositionCallback(GLFWwindow* windowPtr, i32 x, i32 y);
		static void SizeCallback(GLFWwindow* windowPtr, i32 width, i32 height);

		static void FullscreenCallback(bool fullscreen);
		static void MaximizeCallback(GLFWwindow* windowPtr, i32 maximized);
		static void MinimizeCallback(GLFWwindow* windowPtr, i32 minimized);
	};
}
