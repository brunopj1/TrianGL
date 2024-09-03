#pragma once

#include <format>
#include <stdexcept>
#include <string>

namespace TGL
{
	class ShaderCompilationException final : public std::runtime_error
	{
	public:
		ShaderCompilationException(const bool isVertexShader, const std::string& shaderLog)
			: std::runtime_error(std::format("Failed to compile the {} shader: {}", isVertexShader ? "vertex" : "fragment", shaderLog)) {}

		ShaderCompilationException(std::string programLog)
			: std::runtime_error(std::format("Failed to link program: {}", programLog)) {}
	};
}
