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

	class RenderBackend;
	class InputBackend;
	class AudioBackend;

	template <typename T>
	concept IsValidService =
		std::is_base_of_v<Clock, T> ||
		std::is_base_of_v<Window, T> ||
		std::is_base_of_v<InputSystem, T> ||
		std::is_base_of_v<EntityManager, T> ||
		std::is_base_of_v<AssetManager, T> ||
		std::is_base_of_v<RenderBackend, T> ||
		std::is_base_of_v<InputBackend, T> ||
		std::is_base_of_v<AudioBackend, T>;

	template <typename S, typename V>
	concept IsValidServiceOfType =
		std::is_base_of_v<S, V>;

}
