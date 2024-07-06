#pragma once

#include <cassert>

#ifdef DEBUG
#define DECLARE_SPAWNER_ASSERT_VAR(type) static inline i32 s_##type##SpawnerUsageDepth = 0
#else
#define DECLARE_SPAWNER_ASSERT_VAR(type) static_assert(true, "")
#endif

#ifdef DEBUG
#define PREPARE_SPAWNER_ASSERT(type) s_##type##SpawnerUsageDepth += 1
#else
#define PREPARE_SPAWNER_ASSERT(type) static_assert(true, "")
#endif

#ifdef DEBUG
#define PREPARE_SPAWNER_ASSERT_EXT(class, type) class::s_##type##SpawnerUsageDepth += 1
#else
#define PREPARE_SPAWNER_ASSERT_EXT(class, type) static_assert(true, "")
#endif

#define ASSERT_SPAWNER_USAGE_CONSTRUCTOR(spawnerClass, type) assert(spawnerClass::s_##type##SpawnerUsageDepth-- > 0 && "Forbidden direct call to the constructor")
#define ASSERT_SPAWNER_USAGE_DESTRUCTOR(spawnerClass, type) assert(spawnerClass::s_##type##SpawnerUsageDepth-- > 0 && "Forbidden direct call to a destructor")
