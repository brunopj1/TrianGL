#pragma once

namespace TGL
{
    class Quad final
    {
    private:
        friend class AssetManager;
        friend class SpriteRenderer;
        friend class ParticleSystem;
        
    public:
        Quad() = delete;
        ~Quad() = delete;

    private:
        static inline unsigned int s_QuadVao = 0;
        static inline unsigned int s_QuadVbo = 0;
        static inline unsigned int s_QuadEbo = 0;

    private:
        static void Init();
        static void Terminate();

    private:
        static void BindAttributes();
    };
}
