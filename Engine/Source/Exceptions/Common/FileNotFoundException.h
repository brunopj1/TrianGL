#pragma once

#include <format>
#include <stdexcept>
#include <string>

namespace TGL
{
	class FileNotFoundException final : public std::runtime_error
	{
	public:
		FileNotFoundException(const std::string& filePath)
			: std::runtime_error(std::format("The file '{}' was not found", filePath)) {}
	};
}
