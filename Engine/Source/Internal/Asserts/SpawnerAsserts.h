#pragma once

#include <cassert>

// NOLINTBEGIN(CppClangTidyBugproneMacroParentheses)

#ifdef DEBUG
#define DECLARE_SPAWNER_ASSERT_VAR(type)                          \
	static inline i32 s_##type##SpawnerConstructorUsageDepth = 0; \
	static inline i32 s_##type##SpawnerDestructorUsageDepth = 0
#else
#define DECLARE_SPAWNER_ASSERT_VAR(type) static_assert(true, "")
#endif

#ifdef DEBUG
#define PREPARE_SPAWNER_USAGE_CONSTRUCTOR(type)                                           \
	s_##type##SpawnerConstructorUsageDepth += 1;                                          \
	s_##type##SpawnerDestructorUsageDepth += 1;                                           \
	const i32 expectedConstructorUsageDepth = s_##type##SpawnerConstructorUsageDepth - 1; \
	const i32 expectedDestructorUsageDepth = s_##type##SpawnerDestructorUsageDepth
#else
#define PREPARE_SPAWNER_USAGE_CONSTRUCTOR(type) static_assert(true, "")
#endif

#ifdef DEBUG
#define PREPARE_SPAWNER_USAGE_DESTRUCTOR(type)  \
	s_##type##SpawnerDestructorUsageDepth += 1; \
	const i32 expectedDestructorUsageDepth = s_##type##SpawnerDestructorUsageDepth - 1
#else
#define PREPARE_SPAWNER_USAGE_DESTRUCTOR(type) static_assert(true, "")
#endif

#ifdef DEBUG
#define PREPARE_SPAWNER_USAGE_DESTRUCTOR_EXT(class, type) \
	class ::s_##type##SpawnerDestructorUsageDepth += 1;   \
	const i32 expectedDestructorUsageDepth = class ::s_##type##SpawnerDestructorUsageDepth - 1
#else
#define PREPARE_SPAWNER_USAGE_DESTRUCTOR_EXT(class, type) static_assert(true, "")
#endif

#define ASSERT_SPAWNER_USAGE_CONSTRUCTOR(spawnerClass, type) assert(spawnerClass::s_##type##SpawnerConstructorUsageDepth-- > 0 && "Forbidden direct call to the constructor");
#define ASSERT_SPAWNER_USAGE_DESTRUCTOR(spawnerClass, type) assert(spawnerClass::s_##type##SpawnerDestructorUsageDepth-- > 0 && "Forbidden direct call to a destructor")

#ifdef DEBUG
#define ASSERT_POST_SPAWNER_USAGE_CONSTRUCTOR(type)                                                                                                     \
	assert(s_##type##SpawnerConstructorUsageDepth == expectedConstructorUsageDepth && "Something went wrong in the constructor of a managed class"); \
	assert(s_##type##SpawnerDestructorUsageDepth-- == expectedDestructorUsageDepth && "Something went wrong in the constructor of a managed class")
#else
#define ASSERT_POST_SPAWNER_USAGE_CONSTRUCTOR(type) static_assert(true, "")
#endif

#ifdef DEBUG
#define ASSERT_POST_SPAWNER_USAGE_DESTRUCTOR(type) \
	assert(s_##type##SpawnerDestructorUsageDepth == expectedDestructorUsageDepth && "Something went wrong in the destructor of a managed class")
#else
#define ASSERT_POST_SPAWNER_USAGE_DESTRUCTOR(type) static_assert(true, "")
#endif

#ifdef DEBUG
#define ASSERT_POST_SPAWNER_USAGE_DESTRUCTOR_EXT(class, type) \
assert(class ::s_##type##SpawnerDestructorUsageDepth == expectedDestructorUsageDepth && "Something went wrong in the destructor of a managed class")
#else
#define ASSERT_POST_SPAWNER_USAGE_DESTRUCTOR_EXT(class, type) static_assert(true, "")
#endif

// NOLINTEND(CppClangTidyBugproneMacroParentheses)
