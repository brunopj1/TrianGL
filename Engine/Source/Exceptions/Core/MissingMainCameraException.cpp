#include "MissingMainCameraException.h"

using namespace Engine::Exceptions::Core;

const char* MissingMainCameraException::what() const
{
    return "Cannot play without a main camera";
}
