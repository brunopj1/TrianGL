#pragma once

#include <cstdint>

namespace TGL
{
    class IdGenerator
    {
    private:
        friend class Application;

    private:
        uint32_t m_NextId = 1;

    private:
        IdGenerator() = default;
        ~IdGenerator() = default;

    public:
        uint32_t NextId();
        void Reset();
    };
}
