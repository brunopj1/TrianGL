#pragma once

#include <cstdint>

namespace TGL
{
    class IdGenerator
    {
    private:
        friend class Application;

    private:
        uint64_t m_NextId = 1;

    private:
        IdGenerator() = default;
        ~IdGenerator() = default;

    public:
        uint64_t NextId();
        void Reset();
    };
}
