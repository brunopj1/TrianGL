#include "FileNotFoundException.h"

#include <format>

using namespace Engine;

FileNotFoundException::FileNotFoundException(std::string filePath)
    : m_FilePath(std::move(filePath)), m_Message(std::format("The file '{}' was not found", m_FilePath))
{}

const char* FileNotFoundException::what() const
{
    return m_Message.c_str();
}
