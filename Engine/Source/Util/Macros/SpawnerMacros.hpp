#pragma once

#include <type_traits>

#ifdef DEBUG
#include <iostream>
#endif

#define SPAWNER_TEMPLATE_CONDITION(class) \
    std::enable_if_t<                     \
    !std::is_same_v<class, T> &&          \
    std::is_base_of_v<class, T> &&        \
    std::is_constructible_v<T, Args...>>

#define SPAWNER_TEMPLATE_CONDITION_NO_ARGS(class) \
    std::enable_if_t<                             \
    !std::is_same_v<class, T> &&                  \
    std::is_base_of_v<class, T> &&                \
    std::is_constructible_v<T>>


#define SPAWNER_LOOKUP_TEMPLATE_CONDITION(class) \
    std::enable_if_t<                            \
    !std::is_same_v<class, T> &&                 \
    std::is_base_of_v<class, T>>

#ifdef DEBUG
#define DECLARE_SPAWNER_USAGE_VAR() static inline int s_SpawnerUsageDepth = 0
#else
#define DECLARE_SPAWNER_USAGE_VAR() static_assert(true, "")
#endif

#ifdef DEBUG
#define PREPARE_SPAWNER_USAGE() s_SpawnerUsageDepth += 1
#else
#define PREPARE_SPAWNER_USAGE() static_assert(true, "")
#endif

#ifdef DEBUG
#define PREPARE_SPAWNER_USAGE_ALT(spawnerClass) spawnerClass::s_SpawnerUsageDepth += 1
#else
#define PREPARE_SPAWNER_USAGE_ALT(spawnerClass) static_assert(true, "")
#endif

#ifdef DEBUG
#define ASSERT_SPAWNER_USAGE(class, isConstructor)                      \
    if (class::s_SpawnerUsageDepth == 0)                                \
    {                                                                   \
        if (isConstructor)                                              \
        {                                                               \
            std::cerr << "Forbidden direct call to the constructor of " \
                      << #class << "\n";                                \
        }                                                               \
        else                                                            \
        {                                                               \
            std::cerr << "Forbidden direct call to a destructor of "    \
                      << #class << "\n";                                \
        }                                                               \
    }                                                                   \
    else                                                                \
    {                                                                   \
        class::s_SpawnerUsageDepth -= 1;                                \
    }                                                                   \
    static_assert(true, "")
#else
#define ASSERT_SPAWNER_USAGE(class, isConstructor) static_assert(true, "")
#endif
