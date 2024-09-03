#pragma once

//NOLINTBEGIN(CppClangTidyBugproneMacroParentheses)

#ifdef TESTING
#define SERVICE_DESTRUCTOR virtual
#else
#define SERVICE_DESTRUCTOR
#endif

#ifdef TESTING
#define SERVICE_API virtual
#else
#define SERVICE_API
#endif

//NOLINTEND(CppClangTidyBugproneMacroParentheses)