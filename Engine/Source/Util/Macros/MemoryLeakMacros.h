#pragma once

#ifdef DEBUG
#include <iostream>
#endif

// Memory leaks
#ifdef DEBUG
// ReSharper disable once IdentifierTypo, CppInconsistentNaming, bugprone-reserved-identifier, clang-diagnostic-reserved-macro-identifier
#include <crtdbg.h>
#define DEBUG_MEMORY_LEAKS()                                        \
	std::cerr << std::endl;                                         \
	_CrtSetReportMode(_CRT_WARN,  _CRTDBG_MODE_FILE);               \
	_CrtSetReportFile(_CRT_WARN,  _CRTDBG_FILE_STDERR);             \
	_CrtSetReportMode(_CRT_ERROR,  _CRTDBG_MODE_FILE);              \
	_CrtSetReportFile(_CRT_ERROR,  _CRTDBG_FILE_STDERR);            \
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);              \
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);            \
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF )
#else
#define DEBUG_MEMORY_LEAKS() static_assert(true, "")
#endif
