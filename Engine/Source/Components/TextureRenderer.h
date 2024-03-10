#pragma once

#include "Game/Component.h"
#include "Game/Internal/Renderable.h"

// Forward declarations
namespace Engine::Core
{
    class Application;
}

namespace Engine::Resources
{
    class Material;
    class Texture;
}

namespace Engine::DefaultResources
{
    class DefaultMaterial;
}

namespace Engine::Components
{
    class TextureRenderer final : public Game::Component, public Game::Internal::Renderable
    {
    private:
        friend class Core::Application;

    private:
        static inline unsigned int s_QuadVao = 0;
        static inline unsigned int s_QuadVbo = 0;
        static inline unsigned int s_QuadEbo = 0;

    private:
        Resources::Material* m_Material = nullptr;

    public:
        TextureRenderer(Resources::Material* material = nullptr);
        ~TextureRenderer() override = default;

    public:
        Resources::Material* GetMaterial() const;
        void SetMaterial(Resources::Material* material, bool unloadPreviousMaterial = false);
        DefaultResources::DefaultMaterial* UseDefaultMaterial(bool unloadPreviousMaterial = false);

    private:
        static void Init();
        static void Terminate();

    private:
        void Render() override;
    };
}
