#pragma once

#include <iostream>

// Memory Leaks
#ifdef DEBUG
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
#define DEBUG_MEMORY_LEAKS() ;
#endif

// GL Errors
#ifdef DEBUG
#define GL(x)                                                                                                  \
    x;                                                                                                         \
    {                                                                                                          \
        int glError = glGetError();                                                                            \
        if (glError != GL_NO_ERROR)                                                                            \
        {                                                                                                      \
			std::cerr << "OpenGL Error: " << glError << " near '" << __FILE__ << ":" << __LINE__ << std::endl; \
            exit(glError);                                                                                     \
        }                                                                                                      \
    }																										   \
	(void) 0
#else
#define GL(x) x
#endif
