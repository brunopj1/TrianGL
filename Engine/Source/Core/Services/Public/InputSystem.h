#pragma once

#include "Internal/Macros/MockingMacros.h"
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
		friend class ServiceCollection;
		friend struct ServiceDeleter<InputSystem>;

		friend class InputBackend;

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
		MOCKABLE_DESTRUCTOR ~InputSystem() = default;

	public:
		MOCKABLE_METHOD bool IsKeyDown(KeyCode key) const;
		MOCKABLE_METHOD bool WasKeyPressed(KeyCode key) const;
		MOCKABLE_METHOD bool WasKeyRepeated(KeyCode key) const;
		MOCKABLE_METHOD bool WasKeyReleased(KeyCode key) const;

		MOCKABLE_METHOD bool IsMouseButtonDown(MouseButton button) const;
		MOCKABLE_METHOD bool WasMouseButtonPressed(MouseButton button) const;
		MOCKABLE_METHOD bool WasMouseButtonReleased(MouseButton button) const;

		MOCKABLE_METHOD glm::ivec2 GetMousePosition() const;
		MOCKABLE_METHOD glm::ivec2 GetMouseDelta() const;
		MOCKABLE_METHOD void SetMousePosition(glm::ivec2 position);

		MOCKABLE_METHOD i32 GetMouseScroll() const;

		MOCKABLE_METHOD MouseMode GetMouseMode() const;
		MOCKABLE_METHOD void SetMouseMode(MouseMode mode);

	protected:
		MOCKABLE_METHOD void Init(GLFWwindow* windowPtr);

	protected:
		MOCKABLE_METHOD void OnEndOfFrame();
		MOCKABLE_METHOD void PollEvents();

	protected:
		static void KeyboardCallback(GLFWwindow* windowPtr, i32 key, i32 scancode, i32 action, i32 mods);
		static void MouseButtonCallback(GLFWwindow* windowPtr, i32 button, i32 action, i32 mods);
		static void MousePositionCallback(GLFWwindow* windowPtr, f64 x, f64 y);
		static void MouseScrollCallback(GLFWwindow* windowPtr, f64 x, f64 y);
	};
}
