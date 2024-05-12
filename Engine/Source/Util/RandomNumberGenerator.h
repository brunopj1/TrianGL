#pragma once

namespace TGL
{
    class RandomNumberGenerator
    {
    private:
        friend class Application;
        
    private:
        unsigned int m_Seed;
        
    public:
        RandomNumberGenerator(); // Will use a random seed
        RandomNumberGenerator(unsigned int seed);
        ~RandomNumberGenerator() = default;

    public:
        bool GetBool();
        
        int GetInt();
        int GetInt(int min, int max);
        
        unsigned int GetUint();
        unsigned int GetUint(unsigned int min, unsigned int max);
        
        float GetFloat();
        float GetFloat(float min, float max);
        
        double GetDouble();
        double GetDouble(double min, double max);

    private:
        void UpdateSeed();
    };
}


