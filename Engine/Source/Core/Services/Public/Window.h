#pragma once

#include "Core/Internal/Macros/TestMacros.h"
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
		friend class ServiceCollection;
		friend struct ServiceDeleter<Window>;

		friend class InputBackend;

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
		MOCKABLE_DESTRUCTOR ~Window() = default;

	public:
		MOCKABLE_METHOD bool IsFullscreen() const;
		MOCKABLE_METHOD void SetFullscreen(bool fullscreen);

		MOCKABLE_METHOD bool IsMaximized() const;
		MOCKABLE_METHOD void Maximize();

		MOCKABLE_METHOD bool IsMinimized() const;
		MOCKABLE_METHOD void Minimize();

		MOCKABLE_METHOD void Restore();

		MOCKABLE_METHOD std::string GetTitle();
		MOCKABLE_METHOD void SetTitle(const std::string& title);

		MOCKABLE_METHOD glm::ivec2 GetPosition() const;
		MOCKABLE_METHOD void SetPosition(glm::ivec2 position);

		MOCKABLE_METHOD glm::uvec2 GetResolution() const;
		MOCKABLE_METHOD void SetResolution(glm::uvec2 resolution);

		MOCKABLE_METHOD f32 GetAspectRatio() const;

		MOCKABLE_METHOD bool IsVsync() const;
		MOCKABLE_METHOD void SetVsync(bool vsync);

		MOCKABLE_METHOD void Close();
		MOCKABLE_METHOD bool IsClosing() const;

	protected:
		MOCKABLE_METHOD GLFWwindow* Init(std::string title, glm::ivec2 position, glm::uvec2 resolution, bool fullscreen, bool vsync);
		MOCKABLE_METHOD void Terminate() const;

	protected:
		MOCKABLE_METHOD GLFWwindow* GetGlfwWindow() const;

	protected:
		static void CloseCallback(GLFWwindow* windowPtr);

		static void PositionCallback(GLFWwindow* windowPtr, i32 x, i32 y);
		static void SizeCallback(GLFWwindow* windowPtr, i32 width, i32 height);

		static void FullscreenCallback(bool fullscreen);
		static void MaximizeCallback(GLFWwindow* windowPtr, i32 maximized);
		static void MinimizeCallback(GLFWwindow* windowPtr, i32 minimized);
	};
}
