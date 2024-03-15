#pragma once

#include <type_traits>
#include <cassert>

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
#define DECLARE_SPAWNER_USAGE_VAR() ((void)0)
#endif

#ifdef DEBUG
#define PREPARE_SPAWNER_USAGE() s_SpawnerUsageDepth += 1
#else
#define PREPARE_SPAWNER_USAGE() ((void)0)
#endif

#ifdef DEBUG
#define PREPARE_SPAWNER_USAGE_EXTERNAL(spawnerClass) spawnerClass::s_SpawnerUsageDepth += 1
#else
#define PREPARE_SPAWNER_USAGE_ALT(spawnerClass) ((void)0)
#endif

#define ASSERT_SPAWNER_USAGE_CONSTRUCTOR(class) assert(class::s_SpawnerUsageDepth-- > 0 && "Forbidden direct call to the constructor")
#define ASSERT_SPAWNER_USAGE_DESTRUCTOR(class) assert(class::s_SpawnerUsageDepth-- > 0 && "Forbidden direct call to a destructor")
