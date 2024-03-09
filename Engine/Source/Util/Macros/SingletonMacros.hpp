#pragma once

#include <type_traits>
#include "Exceptions/Core/ApplicationNotYetInitialized.hpp"
#include "Exceptions/Core/ForbiddenCallToConstructor.hpp"

#ifdef DEBUG
#include <iostream>
#endif

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
#define SINGLETON_CHECK_IF_INITIALIZED(name)                    \
    if (s_Instance == nullptr)			                        \
    {                                                           \
        throw Exceptions::Core::ApplicationNotYetInitialized(); \
    }                                                           \
    static_assert(true, "")
#else
#define SINGLETON_CHECK_IF_INITIALIZED(name) static_assert(true, "")
#endif

#ifdef DEBUG
#define DECLARE_SINGLETON_USAGE_VAR() static inline int s_SingletonUsageDepth = 0
#else
#define DECLARE_SINGLETON_USAGE_VAR() static_assert(true, "")
#endif

#ifdef DEBUG
#define PREPARE_SINGLETON_USAGE() s_SingletonUsageDepth += 1
#else
#define PREPARE_SINGLETON_USAGE() static_assert(true, "")
#endif

#ifdef DEBUG
#define ASSERT_SINGLETON_USAGE(serviceClass, objectClass, isConstructor)            \
    if (serviceClass::s_SingletonUsageDepth == 0)                                       \
    {                                                                                   \
        if (isConstructor)                                                              \
        {                                                                               \
            std::cerr << "Forbidden direct call to the constructor of a "               \
                      << #objectClass << "\n";                                          \
        }                                                                               \
        else                                                                            \
        {                                                                               \
            std::cerr << "Forbidden direct call to a destructor of a (or from with a) " \
                      << #objectClass << "\n";                                          \
        }                                                                               \
    }                                                                                   \
    else                                                                                \
    {                                                                                   \
        serviceClass::s_SingletonUsageDepth -= 1;                                       \
    }                                                                                   \
    static_assert(true, "")
#else
#define ASSERT_SINGLETON_USAGE(class, name) static_assert(true, "")
#endif
