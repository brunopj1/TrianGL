#pragma once

#include <Game/Entity.h>

namespace TGL
{
    class Camera final : public Entity
    {
    private:
        friend class Application;
        friend class Window;
        friend class Material;

    private:
        static inline Camera* s_MainCamera = nullptr;

    private:
        float m_HorizontalSize = 10.0f;
        bool m_LockHorizontalSize = true;
        float m_AspectRatio;

        glm::ivec2 m_DepthRange = {-1000, 1000};

    private:
        glm::vec3 m_BackgroundColor = {0.5f, 0.5f, 0.5f};

    private:
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ProjectionViewMatrix;

    public:
        Camera(bool setAsMainCamera = false);
        ~Camera() override;

    public:
        static Camera* GetMainCamera();
        void SetAsMainCamera();

    public:
        glm::vec2 GetSize() const;

        float GetHorizontalSize() const;
        void SetHorizontalSize(float size, bool lock = false);

        float GetVerticalSize() const;
        void SetVerticalSize(float size, bool lock = false);

        void LockSize(bool horizontally);
        bool IsSizeLockedHorizontally() const;

        float GetAspectRatio() const;

        void SetDepthRange(int min, int max);
        glm::vec2 GetDepthRange() const;

    public:
        glm::vec3 GetBackgroundColor() const;
        void SetBackgroundColor(const glm::vec3& color);

    public:
        // TODO optimize the matrix calculations for these methods
        glm::vec2 ScreenToWorldPosition(const glm::vec2& screenPos) const;
        glm::vec2 WorldToScreenPosition(const glm::vec2& worldPos) const;

    private:
        void SetAspectRatio(float aspectRatio);

    private:
        void UpdateMatrices();

        glm::mat4 ComputeViewMatrix() const;
        glm::mat4 ComputeProjectionMatrix() const;
        glm::mat4 ComputeProjectionViewMatrix(bool inverse = false) const;

        const glm::mat4& GetViewMatrix() const;
        const glm::mat4& GetProjectionMatrix() const;
        const glm::mat4& GetProjectionViewMatrix() const;
    };
}
