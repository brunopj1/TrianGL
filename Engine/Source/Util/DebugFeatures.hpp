#pragma once

#include <iostream>

// Memory Leaks
#ifdef DEBUG
// ReSharper disable once CppInconsistentNaming
#define _CRTDBG_MAP_ALLOC  // NOLINT(bugprone-reserved-identifier, clang-diagnostic-reserved-macro-identifier)
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
#define DEBUG_MEMORY_LEAKS() ;
#endif
