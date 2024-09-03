#pragma once

#include <format>
#include <stdexcept>
#include <string>

namespace TGL
{
	class ForbiddenCallToConstructor final : public std::runtime_error
	{
	private:
		std::string m_Message;

	public:
		ForbiddenCallToConstructor(const bool isConstructor, std::string objectType)
			: std::runtime_error(std::format("Forbidden call to {} {}", objectType, isConstructor ? "constructor" : "destructor")) {}
	};
}
