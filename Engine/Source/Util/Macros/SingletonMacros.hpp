#pragma once

#include <type_traits>
#include "Exceptions/Core/ServiceNotYetInitialized.h"
#include "Exceptions/Core/SingletonNotBeingUsedException.h"

// Template macros

#define SINGLETON_TEMPLATE_SPAWN_CONDITION(class) \
    std::enable_if_t<                             \
        !std::is_same_v<class, T> &&              \
        std::is_base_of_v<class, T> &&            \
        std::is_constructible_v<T, Args...>>

#define SINGLETON_TEMPLATE_SPAWN_CONDITION_NO_ARGS(class) \
    std::enable_if_t<                                     \
        !std::is_same_v<class, T> &&                      \
        std::is_base_of_v<class, T> &&                    \
        std::is_constructible_v<T>>

#define SINGLETON_TEMPLATE_LOOKUP_CONDITION(class) \
    std::enable_if_t<                              \
        !std::is_same_v<class, T> &&               \
        std::is_base_of_v<class, T>>

// Debug macros

#ifdef DEBUG
#define SINGLETON_CHECK_IF_INITIALIZED(name)                 \
if (s_Instance == nullptr)			                            \
{                                                           \
    throw Exceptions::Core::ServiceNotYetInitialized(name); \
}                                                           \
static_assert(true, "")
#else
#define SINGLETON_CHECK_IF_INITIALIZED(name) static_assert(true, "")
#endif

#ifdef DEBUG
#define DECLARE_SINGLETON_USAGE_VAR() static inline bool s_IsCurrentlyInUse = false
#else
#define DECLARE_SINGLETON_USAGE_VAR() static_assert(true, "")
#endif

#ifdef DEBUG
#define PREPARE_SINGLETON_USAGE(value) s_IsCurrentlyInUse = value
#else
#define PREPARE_SINGLETON_USAGE(value) static_assert(true, "")
#endif

#ifdef DEBUG
#define ASSERT_SINGLETON_USAGE(class, name)                               \
if (!class::s_IsCurrentlyInUse)                                           \
{                                                                         \
    throw Exceptions::Core::SingletonNotBeingUsedException(name, #class); \
}                                                                         \
static_assert(true, "")
#else
#define ASSERT_SINGLETON_USAGE(class, name) static_assert(true, "")
#endif
