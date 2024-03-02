#include "GameModeAlreadySetException.h"

using namespace Engine::Exceptions::Core;

const char* GameModeAlreadySetException::what() const
{
    return "Trying to set the GameMode when it has already been set.";
}
