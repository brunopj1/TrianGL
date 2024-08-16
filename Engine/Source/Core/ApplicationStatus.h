#pragma once

namespace TGL
{
    enum class ApplicationStatusValue : u8
    {
        Closed       = 0,
        Initializing = 1 << 0,
        PostInit     = 1 << 1,
        Running      = 1 << 2,
        PostRun      = 1 << 3,
        Terminating  = 1 << 4
    };

    class ApplicationStatus
    {
    private:
        friend class Application;
        
    private:
        static inline ApplicationStatusValue s_Value = ApplicationStatusValue::Closed;

    public:
        static bool AreServicesAvailable()
        {
            constexpr u8 availableStates =
                static_cast<u8>(ApplicationStatusValue::Initializing) |
                static_cast<u8>(ApplicationStatusValue::Running) |
                static_cast<u8>(ApplicationStatusValue::Terminating);
            
            return (static_cast<u8>(s_Value) & availableStates) != 0;
        }

    private:
        static void SetStatus(const ApplicationStatusValue value)
        {
            s_Value = value;
        }

        static ApplicationStatusValue GetStatus()
        {
            return s_Value;
        }
        
    public:
        ApplicationStatus() = delete;
        ~ApplicationStatus() = delete;
    };
}
