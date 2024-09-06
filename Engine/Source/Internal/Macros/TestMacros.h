#pragma once

#ifdef TESTING
#define TEST_RUN_PRIVACY() public:
#else
#define TEST_RUN_PRIVACY() private:
#endif
