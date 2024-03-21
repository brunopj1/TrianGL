#pragma once
#include <cstdint>

namespace TGL
{
    class Object
    {
    private:
        friend class EntityManager;

    private:
        uint64_t m_Id = 0;

    public:
        Object() = default;
        virtual ~Object() = default;
    };
}
