#pragma once

namespace Engine
{
    class ManagedResource
    {
    private:
        friend class ResourceManager;

    protected:
        ManagedResource() = default;
        virtual ~ManagedResource() = default;

    public:
        virtual void Unload() = 0;
    };
}
