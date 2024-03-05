#pragma once

#include "Game/Component.h"
#include "Game/Internal/IRenderable.h"
#include <glm/mat4x4.hpp>

namespace Engine::Resources
{
    class Texture;
}

namespace Engine::Components
{
    class TextureRenderer final : public Game::Component, public Game::Internal::IRenderable
    {
    private:
        friend class Core::EntityManager;

    private:
        // TODO replace this by a default material
        static inline unsigned int s_QuadVao = 0;
        static inline unsigned int s_QuadVbo = 0;
        static inline unsigned int s_QuadEbo = 0;

        static inline unsigned int s_ShaderProgram = 0;
        static inline unsigned int s_VertexShader = 0;
        static inline unsigned int s_FragmentShader = 0;

        static inline Resources::Texture* s_Texture = nullptr;

    public:
        TextureRenderer();
        ~TextureRenderer() override = default;

    private:
        static void Initialize();
        static void Terminate();

    private:
        void Render(const glm::mat4& projectionViewMatrix) const override;
    };
}
