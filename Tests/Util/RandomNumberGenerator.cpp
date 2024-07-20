#include "Util/RandomNumberGenerator.h"

#include "gtest/gtest.h"

namespace RandomNumberGenerator
{
    TEST(RandomNumberGenerator, Constructors)
    {
        TGL::RandomNumberGenerator rng1{};
        TGL::RandomNumberGenerator rng2{ 12345 };
    }
}