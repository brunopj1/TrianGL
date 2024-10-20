#pragma once

#include <cassert>

#ifdef DEBUG
#define DECLARE_ASSET_FACTORY_VAR(type) \
	static inline i32 s_##type##ConstructorUsageDepth = 0
#else
#define DECLARE_ASSET_FACTORY_VAR(type) static_assert(true, "")
#endif

#ifdef DEBUG
#define DECLARE_ASSET_FACTORY_DESTRUCTOR_VAR() \
	static inline i32 s_AssetDestructorUsageDepth = 0
#else
#define DECLARE_ASSET_FACTORY_DESTRUCTOR_VAR() static_assert(true, "")
#endif

#ifdef DEBUG
#define PREPARE_ASSET_FACTORY_CONSTRUCTOR(type)                                    \
	s_##type##ConstructorUsageDepth += 1;                                          \
	AssetFactoryUtil::s_AssetDestructorUsageDepth += 1;                            \
	const i32 expectedConstructorUsageDepth = s_##type##ConstructorUsageDepth - 1; \
	const i32 expectedDestructorUsageDepth = AssetFactoryUtil::s_AssetDestructorUsageDepth
#else
#define PREPARE_ASSET_FACTORY_CONSTRUCTOR(type) static_assert(true, "")
#endif

#ifdef DEBUG
#define PREPARE_ASSET_FACTORY_DESTRUCTOR()              \
	AssetFactoryUtil::s_AssetDestructorUsageDepth += 1; \
	const i32 expectedDestructorUsageDepth = AssetFactoryUtil::s_AssetDestructorUsageDepth - 1
#else
#define PREPARE_ASSET_FACTORY_DESTRUCTOR() static_assert(true, "")
#endif

#define ASSERT_ASSET_FACTORY_CONSTRUCTOR(type) assert(AssetManager::s_##type##ConstructorUsageDepth-- > 0 && "Forbidden direct call to an Asset constructor of type:" #type)
#define ASSERT_ASSET_FACTORY_DESTRUCTOR() assert(AssetFactoryUtil::s_AssetDestructorUsageDepth-- > 0 && "Forbidden direct call to an Asset destructor")

#ifdef DEBUG
#define ASSERT_POST_ASSET_FACTORY_CONSTRUCTOR(type)                                                                                            \
	assert(s_##type##ConstructorUsageDepth == expectedConstructorUsageDepth && "Something went wrong in an Asset constructor of type:" #type); \
	assert(AssetFactoryUtil::s_AssetDestructorUsageDepth-- == expectedDestructorUsageDepth && "Something went wrong in an Asset constructor of type:" #type)
#else
#define ASSERT_POST_ASSET_FACTORY_CONSTRUCTOR(type) static_assert(true, "")
#endif

#ifdef DEBUG
#define ASSERT_POST_ASSET_FACTORY_DESTRUCTOR() \
	assert(AssetFactoryUtil::s_AssetDestructorUsageDepth == expectedDestructorUsageDepth && "Something went wrong in an Asset destructor")
#else
#define ASSERT_POST_ASSET_FACTORY_DESTRUCTOR() static_assert(true, "")
#endif
