#include "Implementations/Entities/Camera.h"

#include "Core/Services/Private/EntityManager.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

// Mock services

namespace
{
	class MockEntityManager final : public EntityManager
	{
	public:
		static inline u32 s_RenderCalls = 0;

		MockEntityManager()
		{
			s_RenderCalls = 0;
		}

	protected:
		void Render() const override
		{
			EntityManager::Render();

			s_RenderCalls++;
		}
	};

	class MockRenderBackend final : public RenderBackend
	{
	public:
		static inline glm::vec3 s_ClearColor = {0.0f, 0.0f, 0.0f};

		void ClearBuffers(const glm::vec3& color) override
		{
			s_ClearColor = color;
		}
	};

	void MockServiceBuilder(ServiceCollection& collection)
	{
		collection.CreateService<MockEntityManager>();
		collection.CreateService<MockRenderBackend>();
	}
}

// Tests

BEGIN_GAME_TEST(Camera, MainCamera)
{
	void OnUpdate(f32 deltaTime) override
	{
		EXPECT_EQ(Camera::GetMainCamera(), nullptr);

		Camera* camera1 = SpawnEntity<Camera>(true);
		EXPECT_EQ(Camera::GetMainCamera(), camera1);

		Camera* camera2 = SpawnEntity<Camera>(false);
		EXPECT_EQ(Camera::GetMainCamera(), camera1);

		camera2->SetAsMainCamera();
		EXPECT_EQ(Camera::GetMainCamera(), camera2);

		camera2->Destroy();
		EXPECT_EQ(Camera::GetMainCamera(), nullptr);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(Camera, Render, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			EXPECT_EQ(Camera::GetMainCamera(), nullptr);
			EXPECT_EQ(MockEntityManager::s_RenderCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(Camera::GetMainCamera(), nullptr);
			EXPECT_EQ(MockEntityManager::s_RenderCalls, 0);

			Camera* camera = SpawnEntity<Camera>(true);
			EXPECT_EQ(Camera::GetMainCamera(), camera);
		}

		if (frame == 3)
		{
			ASSERT_NE(Camera::GetMainCamera(), nullptr);
			EXPECT_EQ(MockEntityManager::s_RenderCalls, 1);
		}

		if (frame == 4)
		{
			ASSERT_NE(Camera::GetMainCamera(), nullptr);
			EXPECT_EQ(MockEntityManager::s_RenderCalls, 2);

			Camera::GetMainCamera()->Destroy();
		}

		if (frame == 5)
		{
			EXPECT_EQ(Camera::GetMainCamera(), nullptr);
			EXPECT_EQ(MockEntityManager::s_RenderCalls, 2);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Camera, Size)
{
	void OnUpdate(f32 deltaTime) override
	{
		Camera* camera = SpawnEntity<Camera>(true);
		Window& window = Window::Get();

		EXPECT_EQ(window.GetAspectRatio(), camera->GetAspectRatio());

		window.SetResolution({800, 400});
		ASSERT_NEAR(window.GetAspectRatio(), 2.0f, 0.0001f);
		EXPECT_EQ(window.GetAspectRatio(), camera->GetAspectRatio());

		camera->SetHorizontalSize(10.0f);
		const glm::uvec2 size1 = camera->GetSize();
		ASSERT_NEAR(camera->GetHorizontalSize(), size1.x, 0.0001f);
		ASSERT_NEAR(camera->GetVerticalSize(), size1.y, 0.0001f);
		ASSERT_NEAR(size1.x, 10.0f, 0.0001f);
		ASSERT_NEAR(size1.y, 5.0f, 0.0001f);

		camera->SetVerticalSize(10.0f);
		const glm::uvec2 size2 = camera->GetSize();
		ASSERT_NEAR(camera->GetHorizontalSize(), size2.x, 0.0001f);
		ASSERT_NEAR(camera->GetVerticalSize(), size2.y, 0.0001f);
		ASSERT_NEAR(size2.x, 20.0f, 0.0001f);
		ASSERT_NEAR(size2.y, 10.0f, 0.0001f);

		EXPECT_THROW(camera->SetHorizontalSize(0.0f), std::invalid_argument);
		EXPECT_THROW(camera->SetHorizontalSize(-10.0f), std::invalid_argument);

		EXPECT_THROW(camera->SetVerticalSize(0.0f), std::invalid_argument);
		EXPECT_THROW(camera->SetVerticalSize(-10.0f), std::invalid_argument);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Camera, DepthRange)
{
	void OnUpdate(f32 deltaTime) override
	{
		Camera* camera = SpawnEntity<Camera>(true);

		camera->SetDepthRange(-1000, 1000);
		const glm::ivec2 depthRange1 = camera->GetDepthRange();
		EXPECT_EQ(depthRange1.x, -1000);
		EXPECT_EQ(depthRange1.y, 1000);

		camera->SetDepthRange(1000, 2000);
		const glm::ivec2 depthRange2 = camera->GetDepthRange();
		EXPECT_EQ(depthRange2.x, 1000);
		EXPECT_EQ(depthRange2.y, 2000);

		camera->SetDepthRange(-2000, -1000);
		const glm::ivec2 depthRange3 = camera->GetDepthRange();
		EXPECT_EQ(depthRange3.x, -2000);
		EXPECT_EQ(depthRange3.y, -1000);

		ASSERT_THROW(camera->SetDepthRange(1000, 1000), std::invalid_argument);
		ASSERT_THROW(camera->SetDepthRange(1000, -1000), std::invalid_argument);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(Camera, BackgroundColor, MockServiceBuilder)
{
	Camera* m_Camera = nullptr;

	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			m_Camera = SpawnEntity<Camera>(true);

			m_Camera->SetBackgroundColor({0.1f, 0.2f, 0.3f});
			const glm::vec3 color = m_Camera->GetBackgroundColor();
			ASSERT_NEAR(color.x, 0.1f, 0.0001f);
			ASSERT_NEAR(color.y, 0.2f, 0.0001f);
			ASSERT_NEAR(color.z, 0.3f, 0.0001f);
		}

		if (frame == 2)
		{
			ASSERT_NEAR(MockRenderBackend::s_ClearColor.x, 0.1f, 0.0001f);
			ASSERT_NEAR(MockRenderBackend::s_ClearColor.y, 0.2f, 0.0001f);
			ASSERT_NEAR(MockRenderBackend::s_ClearColor.z, 0.3f, 0.0001f);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Camera, CoordinateConversion)
{
	void OnUpdate(f32 deltaTime) override
	{
		Window& window = Window::Get();
		window.SetResolution({500, 500});

		Camera* camera = SpawnEntity<Camera>(true);
		Transform& transform = camera->GetTransform();
		transform.SetPosition({0.0f, 0.0f});
		transform.SetRotationDeg(0.0f);
		camera->SetHorizontalSize(10.0f);

		const glm::vec2 screenCoords1 = camera->WorldToScreenPosition({0.0f, 0.0f});
		ASSERT_NEAR(screenCoords1.x, 250.0f, 0.0001f);
		ASSERT_NEAR(screenCoords1.y, 250.0f, 0.0001f);

		const glm::vec2 screenCoords2 = camera->WorldToScreenPosition({-2.5f, 2.5f});
		ASSERT_NEAR(screenCoords2.x, 125, 0.0001f);
		ASSERT_NEAR(screenCoords2.y, 125, 0.0001f);

		const glm::vec2 worldCoords1 = camera->ScreenToWorldPosition({250.0f, 250.0f});
		ASSERT_NEAR(worldCoords1.x, 0.0f, 0.0001f);
		ASSERT_NEAR(worldCoords1.y, 0.0f, 0.0001f);

		const glm::vec2 worldCoords2 = camera->ScreenToWorldPosition({-1000.0f, 750.0f});
		ASSERT_NEAR(worldCoords2.x, -25.0f, 0.0001f);
		ASSERT_NEAR(worldCoords2.y, -10.0f, 0.0001f);

		transform.SetPosition({-237.123f, 93789.541f});
		transform.SetRotationDeg(73.59f);

		constexpr glm::vec2 worldCoords3 = glm::vec2{372.23f, -8865.04f};
		const glm::vec2 screenCoords3 = camera->WorldToScreenPosition(worldCoords3);
		const glm::vec2 worldCoords4 = camera->ScreenToWorldPosition(screenCoords3);
		ASSERT_NEAR(worldCoords3.x, worldCoords4.x, 0.01f);
		ASSERT_NEAR(worldCoords3.y, worldCoords4.y, 0.01f);

		EndTest();
	}
}
END_GAME_TEST()
