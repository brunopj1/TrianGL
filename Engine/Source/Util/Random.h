#pragma once

namespace TGL
{
    class Random
    {
    private:
        friend class Application;
        
    private:
        static inline unsigned int s_Seed;
        
    public:
        Random() = delete;
        ~Random() = delete;

    public:
        static int GetInt();
        static int GetInt(int min, int max);
        
        static unsigned int GetUint();
        static unsigned int GetUint(unsigned int min, unsigned int max);
        
        static float GetFloat();
        static float GetFloat(float min, float max);
        
        static double GetDouble();
        static double GetDouble(double min, double max);

    private:
        static void InitSeed();
        static void UpdateSeed();
    };
}


