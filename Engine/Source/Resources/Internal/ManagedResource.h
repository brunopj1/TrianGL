#pragma once

namespace Engine::Services
{
    class ResourceManager;
}

namespace Engine::Resources::Internal
{
    class ManagedResource
    {
    private:
        friend class Services::ResourceManager;

    protected:
        ManagedResource() = default;
        virtual ~ManagedResource() = default;
    };
}
