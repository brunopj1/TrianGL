#pragma once

#include "Game/Entity.h"

namespace Engine
{
    class Camera final : public Entity
    {
    private:
        friend class Window;
        friend class Material;

    private:
        static inline Camera* s_MainCamera = nullptr;

    private:
        float m_HorizontalSize = 10.0f;
        bool m_LockHorizontalSize = true;
        float m_AspectRatio;

    private:
        glm::vec3 m_BackgroundColor = {0.5f, 0.5f, 0.5f};

    public:
        Camera(bool setAsMainCamera = false);
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

    public:
        glm::vec3 GetBackgroundColor() const;
        void SetBackgroundColor(const glm::vec3& color);

    private:
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;
        glm::mat4 GetProjectionViewMatrix() const;

        // TODO update the matrix once per frame and save it in a member variable
    };
}
