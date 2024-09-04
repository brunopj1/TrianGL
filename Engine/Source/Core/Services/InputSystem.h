#pragma once

#include "Internal/Macros/ServiceMacros.h"
#include <Core/DataTypes.h>
#include <Core/InputCodes.h>
#include <Core/Service.h>
#include <glm/vec2.hpp>
#include <unordered_set>

// TODO dont register the input if the user is interacting with ImGui

// Forward declarations
struct GLFWwindow; // NOLINT(CppInconsistentNaming, IdentifierTypo)

namespace TGL
{
	class InputSystem : public Service<InputSystem> // NOLINT(CppClassCanBeFinal)
	{
	private:
		friend class Application;
		friend class InputLayer;

	protected:
		GLFWwindow* m_WindowPtr = nullptr;

	protected:
		std::unordered_set<KeyCode> m_KeysPressedThisFrame;
		std::unordered_set<KeyCode> m_KeysRepeatedThisFrame;
		std::unordered_set<KeyCode> m_KeysReleasedThisFrame;
		std::unordered_set<KeyCode> m_KeysDown;

		std::unordered_set<MouseButton> m_MouseButtonsPressedThisFrame;
		std::unordered_set<MouseButton> m_MouseButtonsReleasedThisFrame;
		std::unordered_set<MouseButton> m_MouseButtonsDown;

		glm::ivec2 m_MousePosition = {0, 0};
		glm::ivec2 m_LastMousePosition = {0, 0};

		glm::ivec2 m_MouseDelta = {0, 0};
		i32 m_MouseScroll = 0;

		MouseMode m_MouseMode = MouseMode::Normal;

	protected:
		InputSystem() = default;
		SERVICE_DESTRUCTOR ~InputSystem() = default;

	public:
		SERVICE_API bool IsKeyDown(KeyCode key) const;
		SERVICE_API bool WasKeyPressed(KeyCode key) const;
		SERVICE_API bool WasKeyRepeated(KeyCode key) const;
		SERVICE_API bool WasKeyReleased(KeyCode key) const;

		SERVICE_API bool IsMouseButtonDown(MouseButton button) const;
		SERVICE_API bool WasMouseButtonPressed(MouseButton button) const;
		SERVICE_API bool WasMouseButtonReleased(MouseButton button) const;

		SERVICE_API glm::ivec2 GetMousePosition() const;
		SERVICE_API glm::ivec2 GetMouseDelta() const;
		SERVICE_API void SetMousePosition(glm::ivec2 position);

		SERVICE_API i32 GetMouseScroll() const;

		SERVICE_API MouseMode GetMouseMode() const;
		SERVICE_API void SetMouseMode(MouseMode mode);

	protected:
		SERVICE_API void Init(GLFWwindow* windowPtr);

	protected:
		SERVICE_API void OnEndOfFrame();
		SERVICE_API void PollEvents();

	protected:
		static void KeyboardCallback(GLFWwindow* windowPtr, i32 key, i32 scancode, i32 action, i32 mods);
		static void MouseButtonCallback(GLFWwindow* windowPtr, i32 button, i32 action, i32 mods);
		static void MousePositionCallback(GLFWwindow* windowPtr, f64 x, f64 y);
		static void MouseScrollCallback(GLFWwindow* windowPtr, f64 x, f64 y);
	};
}
