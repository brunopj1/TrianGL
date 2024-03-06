#pragma once

#include "Game/Entity.h"

// Forward declarations
namespace Engine::Core
{
    class EntityManager;
    class Window;
}

namespace Engine::Resources
{
    class Material;
}

namespace Engine::Entities
{
    class Camera final : public Game::Entity
    {
    private:
        friend class Core::Window;
        friend class Resources::Material;

    private:
        static inline Camera* s_MainCamera = nullptr;

    private:
        float m_HorizontalSize = 10.0f;
        bool m_LockHorizontalSize = true;

        float m_AspectRatio;

    public:
        Camera();
        ~Camera() override;

    public:
        static Camera* GetMainCamera();
        void SetAsMainCamera();

    public:
        float GetHorizontalSize() const;
        void SetHorizontalSize(float size, bool lock = false);

        float GetVerticalSize() const;
        void SetVerticalSize(float size, bool lock = false);

        bool IsSizeLockedHorizontally() const;

    private:
        void SetAspectRatio(float aspectRatio);

    private:
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;
        glm::mat4 GetProjectionViewMatrix() const;

        // TODO update the matrix once per frame and save it in a member variable
    };
}
