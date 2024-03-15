#pragma once
#include "Util/Macros/SingletonMacros.hpp"

namespace TGL
{
    class Clock final
    {
    private:
        friend class Application;

    private:
        DECLARE_SINGLETON_INSTANCE_VAR(TGL::Clock);

    private:
        float m_TotalTime = 0.0f;
        float m_DeltaTime = 0.0f;

        unsigned int m_TotalFrameCount = 0;
        unsigned int m_SecondFrameCount = 0;
        unsigned int m_FrameRate = 1;

        float m_NextSecond = 1.0f;
        bool m_IsNewSecond = false;

    private:
        Clock();
        ~Clock();

    private:
        float Update();

    public:
        static float GetTotalTime();
        static float GetDeltaTime();

        static unsigned int GetFrameCount();
        static unsigned int GetFrameRate();

        static bool IsNewSecond();
    };
}
