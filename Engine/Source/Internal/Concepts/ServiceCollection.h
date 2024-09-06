#pragma once

#include <type_traits>

namespace TGL
{
	// Forward declarations
	class Clock;
	class Window;
	class InputSystem;
	class EntityManager;
	class AssetManager;

	template <typename T>
	concept IsValidService =
		std::is_base_of_v<Clock, T> ||
		std::is_base_of_v<Window, T> ||
		std::is_base_of_v<InputSystem, T> ||
		std::is_base_of_v<EntityManager, T> ||
		std::is_base_of_v<AssetManager, T>;

	template <typename S, typename V>
	concept IsValidServiceOfType =
		std::is_base_of_v<S, V>;

}
