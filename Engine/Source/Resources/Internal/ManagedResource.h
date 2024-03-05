#pragma once

namespace Engine::Core
{
    class ResourceManager;
}

namespace Engine::Resources::Internal
{
    class ManagedResource
    {
    private:
        friend class Core::ResourceManager;

    protected:
        ManagedResource() = default;
        virtual ~ManagedResource() = default;
    };
}
