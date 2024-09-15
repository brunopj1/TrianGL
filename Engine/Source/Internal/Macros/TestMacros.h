#pragma once

#ifdef TESTING
#define TEST_RUN_PRIVACY() public:
#else
#define TEST_RUN_PRIVACY() private:
#endif

#ifdef TESTING
#define MOCKABLE_DESTRUCTOR virtual
#else
#define MOCKABLE_DESTRUCTOR
#endif

#ifdef TESTING
#define MOCKABLE_METHOD virtual
#else
#define MOCKABLE_METHOD
#endif
