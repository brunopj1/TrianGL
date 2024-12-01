#pragma once

#include <format>
#include <stdexcept>

namespace TGL
{
	class InvalidMaterialUniformException final : public std::runtime_error
	{
	public:
		InvalidMaterialUniformException(const std::string& uniformName)
			: std::runtime_error(std::format("Could not create the uniform '%s'", uniformName)) {}
	};
}
