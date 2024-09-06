#pragma once

#include "Core/DataTypes.h"
#include "Core/InputCodes.h"
#include "Core/Service.h"
#include "Internal/Macros/MockingMacros.h"
#include "glm/vec2.hpp"
#include <string>

// Forward declarations
struct GLFWwindow; // NOLINT(CppInconsistentNaming, IdentifierTypo)

namespace TGL
{
	class InputBackend : public Service<InputBackend> // NOLINT(CppClassCanBeFinal)
	{
	private:
		friend class ServiceCollection;
		friend struct ServiceDeleter<InputBackend>;

		friend class InputSystem;
		friend class Window;

	protected:
		InputBackend() = default;
		~InputBackend() = default;

	protected:
		MOCKABLE_METHOD void SetWindowCloseCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*));
		MOCKABLE_METHOD void SetWindowPositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32));
		MOCKABLE_METHOD void SetWindowSizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32));
		MOCKABLE_METHOD void SetWindowMaximizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32));
		MOCKABLE_METHOD void SetWindowMinimizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32));

		MOCKABLE_METHOD void SetKeyboardCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32, i32));
		MOCKABLE_METHOD void SetMouseButtonCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32));
		MOCKABLE_METHOD void SetMousePositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64));
		MOCKABLE_METHOD void SetMouseScrollCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64));

	protected:
		MOCKABLE_METHOD void CloseWindow(GLFWwindow* windowPtr);

	protected:
		MOCKABLE_METHOD void SetWindowTitle(GLFWwindow* windowPtr, const std::string& title);
		MOCKABLE_METHOD void SetWindowPosition(GLFWwindow* windowPtr, const glm::ivec2& position);
		MOCKABLE_METHOD void SetWindowResolution(GLFWwindow* windowPtr, const glm::uvec2& resolution);

	protected:
		MOCKABLE_METHOD void SetFullscreen(GLFWwindow* windowPtr, bool fullscreen, const glm::uvec2& position, const glm::uvec2& resolution);
		MOCKABLE_METHOD void MaximizeWindow(GLFWwindow* windowPtr);
		MOCKABLE_METHOD void MinimizeWindow(GLFWwindow* windowPtr);
		MOCKABLE_METHOD void RestoreWindow(GLFWwindow* windowPtr);

	protected:
		MOCKABLE_METHOD void SetMouseInputMode(GLFWwindow* windowPtr, MouseMode mode);

		MOCKABLE_METHOD glm::ivec2 GetMousePosition(GLFWwindow* windowPtr); // Used during initialization
		MOCKABLE_METHOD void SetMousePosition(GLFWwindow* windowPtr, const glm::ivec2& position);

	private:
		MOCKABLE_METHOD void PollEvents();
	};
}
