#pragma once

#include <iostream>
#include "Exceptions/Core/ServiceNotYetInitialized.h"
#include "Exceptions/Core/SingletonNotBeingUsedException.h"

// Debug only operations
#ifdef DEBUG
#define DEBUG_DO(operation) operation
#else
#define DEBUG_DO(operation) static_assert(true, "")
#endif

// @formatter:off

// Memory leaks
#ifdef DEBUG
// ReSharper disable once CppInconsistentNaming, bugprone-reserved-identifier, clang-diagnostic-reserved-macro-identifier
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_MEMORY_LEAKS()                             \
	std::cerr << std::endl;                              \
	_CrtSetReportMode(_CRT_WARN,  _CRTDBG_MODE_FILE);    \
	_CrtSetReportFile(_CRT_WARN,  _CRTDBG_FILE_STDERR);  \
	_CrtSetReportMode(_CRT_ERROR,  _CRTDBG_MODE_FILE);   \
	_CrtSetReportFile(_CRT_ERROR,  _CRTDBG_FILE_STDERR); \
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);   \
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR); \
	_CrtDumpMemoryLeaks()
#else
#define DEBUG_MEMORY_LEAKS() static_assert(true, "")
#endif

// Singleton validation
#ifdef DEBUG
#define DEBUG_SINGLETON_INSTANCE(ptr, name)                     \
	if ((ptr) == nullptr)			                            \
	{                                                           \
		throw Exceptions::Core::ServiceNotYetInitialized(name); \
	}                                                           \
	static_assert(true, "")
#else
#define DEBUG_SINGLETON_INSTANCE(ptr, name) static_assert(true, "")
#endif

#ifdef DEBUG
#define DEBUG_SINGLETON_DECLARE_USAGE_VAR() static inline bool s_IsCurrentlyInUse = false
#else
#define DEBUG_SINGLETON_DECLARE_USAGE_VAR() static_assert(true, "")
#endif

#ifdef DEBUG
#define DEBUG_SINGLETON_ASSERT_USAGE(class, name)                                   \
	if (!class::s_IsCurrentlyInUse)                                          \
    {                                                                        \
    	throw Exceptions::Core::SingletonNotBeingUsedException(name, #class); \
	}                                                                        \
	static_assert(true, "")
#else
#define DEBUG_SINGLETON_ASSERT_USAGE(class, name) static_assert(true, "")
#endif

// @formatter:on
