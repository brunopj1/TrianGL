#pragma once

#include <format>
#include <stdexcept>
#include <string>

namespace TGL
{
	class ShaderLinkingException final : public std::runtime_error
	{
	public:
		ShaderLinkingException(const std::string& programLog)
			: std::runtime_error(std::format("Failed to link program: {}", programLog)) {}
	};
}
