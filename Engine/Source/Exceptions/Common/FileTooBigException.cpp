#include "FileTooBigException.h"

#include <format>

using namespace Engine;

FileTooBigException::FileTooBigException(std::string filePath, std::string maximumSize)
    : m_FilePath(std::move(filePath)), m_Message(std::format("The file '{}' exceeds the maximum size of {}", m_FilePath, maximumSize))
{}

const char* FileTooBigException::what() const
{
    return m_Message.c_str();
}
