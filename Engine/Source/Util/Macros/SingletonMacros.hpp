#pragma once

#include <type_traits>
#include "Exceptions/Core/ApplicationNotYetInitialized.hpp"
#include "Exceptions/Core/ForbiddenCallToConstructor.hpp"

#ifdef DEBUG
#define SINGLETON_CHECK_IF_INITIALIZED()                    \
    if (s_Instance == nullptr)			                    \
    {                                                       \
    throw Exceptions::Core::ApplicationNotYetInitialized(); \
    }                                                       \
static_assert(true, "")
#else
#define SINGLETON_CHECK_IF_INITIALIZED() static_assert(true, "")
#endif

#ifdef DEBUG
#define SINGLETON_CHECK_IF_INITIALIZED_EXTERNAL(class)      \
    if (class::s_Instance == nullptr)			            \
    {                                                       \
    throw Exceptions::Core::ApplicationNotYetInitialized(); \
    }                                                       \
static_assert(true, "")
#else
#define SINGLETON_CHECK_IF_INITIALIZED_EXTERNAL() static_assert(true, "")
#endif
