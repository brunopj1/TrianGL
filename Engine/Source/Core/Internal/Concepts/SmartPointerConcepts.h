#pragma once

#include <type_traits>

namespace TGL
{
	// Forward declarations
	class Entity;
	class Component;

	class Audio;
	class Animation;
	class AnimationFrame;
	class AnimationSprite;
	class Material;
	class Sprite;
	class Texture;
	class TextureSlice;

	template <typename T>
	concept LazyPointerValue =
		std::is_base_of_v<Entity, T> ||
		std::is_base_of_v<Component, T>;

	template <typename T>
	concept SharedPointerValue =
		std::is_same_v<Audio, T> ||
		std::is_same_v<Animation, T> ||
		std::is_same_v<AnimationFrame, T> ||
		std::is_same_v<AnimationSprite, T> ||
		std::is_base_of_v<Material, T> ||
		std::is_same_v<Sprite, T> ||
		std::is_same_v<Texture, T> ||
		std::is_same_v<TextureSlice, T>;

	template <typename From, typename To>
	concept SmartPointerConversion =
		std::is_base_of_v<To, From>;

	template <typename T1, typename T2>
	concept SmartPointerComparison =
		std::is_same_v<T1, T2> ||
		std::is_base_of_v<T1, T2> ||
		std::is_base_of_v<T2, T1>;
}
