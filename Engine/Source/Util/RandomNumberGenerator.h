#pragma once

#include <glm/glm.hpp>

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

        glm::ivec2 GetInt2();
        glm::ivec2 GetInt2(int min, int max);
        glm::ivec2 GetInt2(const glm::ivec2& min, const glm::ivec2& max);

        glm::ivec3 GetInt3();
        glm::ivec3 GetInt3(int min, int max);
        glm::ivec3 GetInt3(const glm::ivec3& min, const glm::ivec3& max);

        glm::ivec4 GetInt4();
        glm::ivec4 GetInt4(int min, int max);
        glm::ivec4 GetInt4(const glm::ivec4& min, const glm::ivec4& max);

        glm::uvec2 GetUint2();
        glm::uvec2 GetUint2(unsigned int min, unsigned int max);
        glm::uvec2 GetUint2(const glm::uvec2& min, const glm::uvec2& max);

        glm::uvec3 GetUint3();
        glm::uvec3 GetUint3(unsigned int min, unsigned int max);
        glm::uvec3 GetUint3(const glm::uvec3& min, const glm::uvec3& max);

        glm::uvec4 GetUint4();
        glm::uvec4 GetUint4(unsigned int min, unsigned int max);
        glm::uvec4 GetUint4(const glm::uvec4& min, const glm::uvec4& max);

        glm::vec2 GetFloat2();
        glm::vec2 GetFloat2(float min, float max);
        glm::vec2 GetFloat2(const glm::vec2& min, const glm::vec2& max);

        glm::vec3 GetFloat3();
        glm::vec3 GetFloat3(float min, float max);
        glm::vec3 GetFloat3(const glm::vec3& min, const glm::vec3& max);

        glm::vec4 GetFloat4();
        glm::vec4 GetFloat4(float min, float max);
        glm::vec4 GetFloat4(const glm::vec4& min, const glm::vec4& max);

    private:
        void UpdateSeed();
    };
}


