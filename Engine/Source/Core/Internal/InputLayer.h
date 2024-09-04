#pragma once

#include "Core/DataTypes.h"
#include "Core/InputCodes.h"
#include "glm/vec2.hpp"
#include <string>

// Forward declarations
struct GLFWwindow; // NOLINT(CppInconsistentNaming, IdentifierTypo)

namespace TGL
{
	class InputLayer final
	{
	private:
		friend class InputSystem;
		friend class Window;

	public:
		InputLayer() = delete;
		~InputLayer() = delete;

	private:
		static void SetWindowCloseCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*));
		static void SetWindowPositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32));
		static void SetWindowSizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32));
		static void SetWindowMaximizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32));
		static void SetWindowMinimizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32));

		static void SetKeyboardCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32, i32));
		static void SetMouseButtonCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32));
		static void SetMousePositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64));
		static void SetMouseScrollCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64));

	private:
		static void CloseWindow(GLFWwindow* windowPtr);

	private:
		static void SetWindowTitle(GLFWwindow* windowPtr, const std::string& title);
		static void SetWindowPosition(GLFWwindow* windowPtr, const glm::ivec2& position);
		static void SetWindowResolution(GLFWwindow* windowPtr, const glm::uvec2& resolution);

	private:
		static void SetFullscreen(GLFWwindow* windowPtr, bool fullscreen, const glm::uvec2& position, const glm::uvec2& resolution);
		static void MaximizeWindow(GLFWwindow* windowPtr);
		static void MinimizeWindow(GLFWwindow* windowPtr);
		static void RestoreWindow(GLFWwindow* windowPtr);

	private:
		static void SetMouseInputMode(GLFWwindow* windowPtr, MouseMode mode);

		static glm::ivec2 GetMousePosition(GLFWwindow* windowPtr); // Used during initialization
		static void SetMousePosition(GLFWwindow* windowPtr, const glm::ivec2& position);

	private:
		static void PollEvents();
	};
}
