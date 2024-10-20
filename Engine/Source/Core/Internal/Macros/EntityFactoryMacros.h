#pragma once

#include <cassert>

#ifdef DEBUG
#define DECLARE_ENTITY_FACTORY_VAR(type)                   \
	static inline i32 s_##type##ConstructorUsageDepth = 0; \
	static inline i32 s_##type##DestructorUsageDepth = 0
#else
#define DECLARE_ENTITY_FACTORY_VAR(type) static_assert(true, "")
#endif

#ifdef DEBUG
#define PREPARE_ENTITY_FACTORY_CONSTRUCTOR(type)                                   \
	s_##type##ConstructorUsageDepth += 1;                                          \
	s_##type##DestructorUsageDepth += 1;                                           \
	const i32 expectedConstructorUsageDepth = s_##type##ConstructorUsageDepth - 1; \
	const i32 expectedDestructorUsageDepth = s_##type##DestructorUsageDepth
#else
#define PREPARE_ENTITY_FACTORY_CONSTRUCTOR(type) static_assert(true, "")
#endif

#ifdef DEBUG
#define PREPARE_ENTITY_FACTORY_DESTRUCTOR(type) \
	s_##type##DestructorUsageDepth += 1;        \
	const i32 expectedDestructorUsageDepth = s_##type##DestructorUsageDepth - 1
#else
#define PREPARE_ENTITY_FACTORY_DESTRUCTOR(type) static_assert(true, "")
#endif

#define ASSERT_ENTITY_FACTORY_CONSTRUCTOR(type) assert(EntityManager::s_##type##ConstructorUsageDepth-- > 0 && "Forbidden direct call to a GameObject constructor of type:" #type)
#define ASSERT_ENTITY_FACTORY_DESTRUCTOR(type) assert(EntityManager::s_##type##DestructorUsageDepth-- > 0 && "Forbidden direct call to a GameObject destructor of type:" #type)

#ifdef DEBUG
#define ASSERT_POST_ENTITY_FACTORY_CONSTRUCTOR(type)                                                                                               \
	assert(s_##type##ConstructorUsageDepth == expectedConstructorUsageDepth && "Something went wrong in a GameObject constructor of type:" #type); \
	assert(s_##type##DestructorUsageDepth-- == expectedDestructorUsageDepth && "Something went wrong in a GameObject constructor of type:" #type)
#else
#define ASSERT_POST_ENTITY_FACTORY_CONSTRUCTOR(type) static_assert(true, "")
#endif

#ifdef DEBUG
#define ASSERT_POST_ENTITY_FACTORY_DESTRUCTOR(type) \
	assert(s_##type##DestructorUsageDepth == expectedDestructorUsageDepth && "Something went wrong in a GameObject destructor of type:" #type)
#else
#define ASSERT_POST_ENTITY_FACTORY_DESTRUCTOR(type) static_assert(true, "")
#endif
