#pragma once

#include "Game/Component.h"
#include "Game/Internal/IRenderable.h"
#include <glm/mat4x4.hpp>

namespace Engine::Resources
{
    class Material;
    class Texture;
}

namespace Engine::Components
{
    class TextureRenderer final : public Game::Component, public Game::Internal::IRenderable
    {
    private:
        friend class Core::EntityManager;

    private:
        static inline unsigned int s_QuadVao = 0;
        static inline unsigned int s_QuadVbo = 0;
        static inline unsigned int s_QuadEbo = 0;

        static inline Resources::Material* s_Material = nullptr;
        // TODO put the texture in the default material
        static inline Resources::Texture* s_Texture = nullptr;

    public:
        TextureRenderer();
        ~TextureRenderer() override = default;

    private:
        static void Init();
        static void Terminate();

    private:
        void Render(const glm::mat4& projectionViewMatrix) const override;
    };
}
