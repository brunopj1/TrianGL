#pragma once

namespace TGL
{
    class ApplicationStatus
    {
    private:
        friend class Application;
        friend class EntityManager;
        friend class AssetManager;
        friend class Window;
        friend class ParticleSystem;

    private:
        static inline bool s_IsAvailable = false;
        
    public:
        ApplicationStatus() = delete;
        ~ApplicationStatus() = delete;
    };
}
