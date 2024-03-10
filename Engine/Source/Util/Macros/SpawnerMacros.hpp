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
#define ASSERT_SPAWNER_USAGE(spawnerClass, objectClass, isConstructor)                  \
    if (spawnerClass::s_SpawnerUsageDepth == 0)                                         \
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
        spawnerClass::s_SpawnerUsageDepth -= 1;                                         \
    }                                                                                   \
    static_assert(true, "")
#else
#define ASSERT_SPAWNER_USAGE(spawnerClass, objectClass, isConstructor) static_assert(true, "")
#endif
