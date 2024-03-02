#include "GameModeAlreadySpecifiedException.h"

using namespace Engine::Exceptions::Core;

const char* GameModeAlreadySpecifiedException::what() const
{
    return "The GameMode has already been specified";
}
