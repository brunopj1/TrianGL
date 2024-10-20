#pragma once

#include "Core/DataTypes.h"
#include "glm/vec2.hpp"

enum class CharacterDirection : u8
{
	Up,
	UpRight,
	Right,
	DownRight,
	Down,
	DownLeft,
	Left,
	UpLeft
};

inline glm::ivec2 GetDirectionVector(const CharacterDirection direction)
{
	switch (direction)
	{
		case CharacterDirection::Up:
			return {0, 1};
		case CharacterDirection::UpRight:
			return {1, 1};
		case CharacterDirection::Right:
			return {1, 0};
		case CharacterDirection::DownRight:
			return {1, -1};
		case CharacterDirection::Down:
			return {0, -1};
		case CharacterDirection::DownLeft:
			return {-1, -1};
		case CharacterDirection::Left:
			return {-1, 0};
		case CharacterDirection::UpLeft:
			return {-1, 1};
	}

	return {0, 0};
}
