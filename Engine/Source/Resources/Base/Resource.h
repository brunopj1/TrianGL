#pragma once

#include <cstdint>
#include <type_traits>

namespace TGL
{
    // Forward declarations
    template <typename T, typename C>
    class LazyPtr;

    class Resource
    {
    private:
        friend class ResourceManager;

        template <typename T, typename C>
        friend class LazyPtr;

    private:
        uint32_t m_Id = 0;

    protected:
        Resource() = default;
        virtual ~Resource() = default;

    public:
        template <typename T, typename = std::enable_if_t<std::is_base_of_v<Resource, T>>>
        T* As()
        {
            return dynamic_cast<T*>(this);
        }

    public:
        virtual void Unload() = 0;
    };
}
