#include "GameModeMissingException.h"

using namespace Engine::Exceptions::Core;

const char* GameModeMissingException::what() const
{
    return "Cannot run the application without a GameMode";
}
