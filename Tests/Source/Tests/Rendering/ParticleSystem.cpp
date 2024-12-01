#include "Rendering/ParticleSystem.h"

#include "General/Camera.h"
#include "Implementations/Materials/DefaultSpriteMaterial.h"
#include "Implementations/ParticleSystems/DefaultParticleSystem.h"
#include "Util/GameTestAbstractions.h"
#include "Util/RandomNumberGenerator.h"

using namespace TGL;

// Mock services

namespace
{
	class MockClock final : public Clock
	{
	protected:
		std::chrono::steady_clock::time_point CalculateCurrentTime() const override
		{
			return m_LastFrameTime + std::chrono::milliseconds(750);
		}
	};

	class MockEntityManager final : public EntityManager
	{
	public:
		static inline Renderable* s_Renderable = nullptr;
		static inline bool s_WasRendered = false;

	protected:
		void Render() const override
		{
			EntityManager::Render();

			s_WasRendered = false;

			for (const Renderable* renderable : m_RenderQueue)
			{
				if (renderable == s_Renderable)
				{
					s_WasRendered = true;
					break;
				}
			}
		}
	};

	class MockRenderBackend final : public RenderBackend
	{
	public:
		static inline u32 s_UseProgramCalls = 0;
		static inline u32 s_DrawElementsInstancedCalls = 0;

	protected:
		void UseProgram(const u32 programId) override
		{
			RenderBackend::UseProgram(programId);
			s_UseProgramCalls++;
		}

		void DrawElementsInstanced(const u32 vao, const u32 ebo, const u32 vertexCount, const u32 instanceCount) override
		{
			RenderBackend::DrawElementsInstanced(vao, ebo, vertexCount, instanceCount);
			s_DrawElementsInstancedCalls++;
		}
	};

	void MockServiceBuilder(ServiceCollection& collection)
	{
		collection.CreateService<MockClock>();
		collection.CreateService<MockEntityManager>();
		collection.CreateService<MockRenderBackend>();
	}
}

// Helper classes

namespace TGL
{
	class TestEntity final : public Entity
	{
	public:
		TestEntity()
			: Entity(false) {}
	};

	class TestMaterial final : public Material
	{
	public:
		TestMaterial()
			: Material("Assets/Shaders/default_particle_test.vert", "Assets/Shaders/default_particle_test.frag")
		{}
	};

	struct TestCpuParticle
	{
		f32 Lifetime;
	};

	struct TestGpuParticle
	{
		static std::vector<ParticleDataInfo> GetParticleStructure()
		{
			return {};
		}
	};

	struct TestParticleSpawnData
	{
		f32 Lifetime;
	};

	class TestParticleSystem final : public ParticleSystem<TestCpuParticle, TestGpuParticle, TestParticleSpawnData>
	{
	public:
		u32 m_SetupCallCount;
		u32 m_UpdateCallCount;

	protected:
		void SetupParticle(const TestParticleSpawnData& spawnData, TestCpuParticle& cpuParticle, TestGpuParticle& gpuParticle) override
		{
			m_SetupCallCount++;
			cpuParticle.Lifetime = spawnData.Lifetime;
		}

		void UpdateParticle(TestCpuParticle& cpuParticle, TestGpuParticle& gpuParticle, const f32 deltaTime) override
		{
			m_UpdateCallCount++;
			cpuParticle.Lifetime -= deltaTime;
		}

		bool IsParticleAlive(const TestCpuParticle& cpuParticle, const TestGpuParticle& gpuParticle) const override
		{
			return cpuParticle.Lifetime > 0.0f;
		}
	};
}

// Tests

BEGIN_GAME_TEST(ParticleSystem, Constructor)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();

		const DefaultParticleSystem* particleSystem1 = entity->AttachComponent<DefaultParticleSystem>();
		EXPECT_EQ(particleSystem1->GetMaxParticles(), 1000);
		EXPECT_EQ(particleSystem1->GetParticleCount(), 0);
		EXPECT_EQ(particleSystem1->GetMaterial(), nullptr);

		const DefaultParticleSystem* particleSystem2 = entity->AttachComponent<DefaultParticleSystem>(543);
		EXPECT_EQ(particleSystem2->GetMaxParticles(), 543);
		EXPECT_EQ(particleSystem2->GetParticleCount(), 0);
		EXPECT_EQ(particleSystem2->GetMaterial(), nullptr);

		const SharedPtr<TestMaterial> material = Material::CreateInstanceOf<TestMaterial>();
		const DefaultParticleSystem* particleSystem3 = entity->AttachComponent<DefaultParticleSystem>(5123, material);
		EXPECT_EQ(particleSystem3->GetMaxParticles(), 5123);
		EXPECT_EQ(particleSystem3->GetParticleCount(), 0);
		EXPECT_EQ(particleSystem3->GetMaterial(), material);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(ParticleSystem, Emit)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		DefaultParticleSystem* particleSystem = entity->AttachComponent<DefaultParticleSystem>();
		EXPECT_EQ(particleSystem->GetParticleCount(), 0);

		ParticleSpawnData spawnData;
		spawnData.Position = glm::vec2(1.0f, 2.0f);
		spawnData.Velocity = glm::vec2(3.0f, 4.0f);
		spawnData.Duration = 5.0f;

		particleSystem->Emit(spawnData);
		EXPECT_EQ(particleSystem->GetParticleCount(), 1);

		RandomNumberGenerator rng;
		for (u32 i = 0; i < 200; i++)
		{
			spawnData.Position = rng.GetFVec2(-10.0f, 10.0f);
			spawnData.Velocity = rng.GetFVec2(-2.0f, 2.0f);
			spawnData.Duration = rng.GetFloat(3.0f, 7.0f);

			particleSystem->Emit(spawnData);
		}
		EXPECT_EQ(particleSystem->GetParticleCount(), 201);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(ParticleSystem, EmitDead)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		DefaultParticleSystem* particleSystem = entity->AttachComponent<DefaultParticleSystem>();
		EXPECT_EQ(particleSystem->GetParticleCount(), 0);

		const bool success1 = particleSystem->Emit({.Duration = 0.0f});
		EXPECT_FALSE(success1);
		EXPECT_EQ(particleSystem->GetParticleCount(), 0);

		const bool success2 = particleSystem->Emit({.Duration = -1.0f});
		EXPECT_FALSE(success2);
		EXPECT_EQ(particleSystem->GetParticleCount(), 0);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(ParticleSystem, MaxParticles)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		DefaultParticleSystem* particleSystem = entity->AttachComponent<DefaultParticleSystem>(10);

		for (u32 i = 0; i < 10; i++)
		{
			const bool success = particleSystem->Emit({.Duration = 1.0f});
			EXPECT_TRUE(success);
		}

		const bool success = particleSystem->Emit({.Duration = 1.0f});
		EXPECT_FALSE(success);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(ParticleSystem, Lifetime, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();
		const f32 time = clock.GetTotalTime();

		static DefaultParticleSystem* particleSystem = nullptr;
		static f32 spawnTime = 0.0f;

		if (frame == 1)
		{
			EXPECT_NEAR(time, 0.750f, 0.001f);

			TestEntity* entity = SpawnEntity<TestEntity>();
			particleSystem = entity->AttachComponent<DefaultParticleSystem>(20);
			EXPECT_EQ(particleSystem->GetParticleCount(), 0);

			for (u32 i = 0; i < 10; i++)
			{
				particleSystem->Emit({.Duration = 1.0f});
				particleSystem->Emit({.Duration = 2.0f});
			}

			EXPECT_EQ(particleSystem->GetParticleCount(), 20);

			spawnTime = time;
		}

		if (frame == 2)
		{
			EXPECT_NEAR(time - spawnTime, 0.750f, 0.001f);
			EXPECT_EQ(particleSystem->GetParticleCount(), 20);
		}

		if (frame == 3)
		{
			EXPECT_NEAR(time - spawnTime, 1.500f, 0.001f);
			EXPECT_EQ(particleSystem->GetParticleCount(), 10);
		}

		if (frame == 4)
		{
			EXPECT_NEAR(time - spawnTime, 2.250f, 0.001f);
			EXPECT_EQ(particleSystem->GetParticleCount(), 0);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(ParticleSystem, SetupAndUpdate, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		static TestParticleSystem* particleSystem = nullptr;
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			TestEntity* entity = SpawnEntity<TestEntity>();
			particleSystem = entity->AttachComponent<TestParticleSystem>();

			EXPECT_EQ(particleSystem->m_SetupCallCount, 0);
			EXPECT_EQ(particleSystem->m_UpdateCallCount, 0);

			particleSystem->Emit({.Lifetime = 1.0f});
			particleSystem->Emit({.Lifetime = 2.0f});

			EXPECT_EQ(particleSystem->m_SetupCallCount, 2);
			EXPECT_EQ(particleSystem->m_UpdateCallCount, 0);
		}

		if (frame == 2)
		{
			EXPECT_EQ(particleSystem->m_SetupCallCount, 2);
			EXPECT_EQ(particleSystem->m_UpdateCallCount, 2);
		}

		if (frame == 3)
		{
			EXPECT_EQ(particleSystem->m_SetupCallCount, 2);
			EXPECT_EQ(particleSystem->m_UpdateCallCount, 4);
		}

		if (frame == 4)
		{
			EXPECT_EQ(particleSystem->m_SetupCallCount, 2);
			EXPECT_EQ(particleSystem->m_UpdateCallCount, 5);
		}

		if (frame == 5)
		{
			EXPECT_EQ(particleSystem->m_SetupCallCount, 2);
			EXPECT_EQ(particleSystem->m_UpdateCallCount, 5);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(ParticleSystem, Material)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		DefaultParticleSystem* particleSystem = entity->AttachComponent<DefaultParticleSystem>();
		EXPECT_EQ(particleSystem->GetMaterial(), nullptr);

		const SharedPtr<DefaultParticleMaterial> defaultMaterial = particleSystem->UseDefaultMaterial();
		EXPECT_EQ(particleSystem->GetMaterial(), defaultMaterial);

		particleSystem->SetMaterial(nullptr);
		EXPECT_EQ(particleSystem->GetMaterial(), nullptr);

		const SharedPtr<TestMaterial> material = Material::CreateInstanceOf<TestMaterial>();
		particleSystem->SetMaterial(material);
		EXPECT_EQ(particleSystem->GetMaterial(), material);

		particleSystem->SetMaterial(nullptr);
		EXPECT_EQ(particleSystem->GetMaterial(), nullptr);

		const SharedPtr<Material> spriteMaterial = Material::CreateInstanceOf<DefaultSpriteMaterial>();
		EXPECT_THROW(particleSystem->SetMaterial(spriteMaterial), IncompatibleMaterialException);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(ParticleSystem, Render, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		if (frame == 1)
		{
			SpawnEntity<Camera>(true);

			Entity* entity = SpawnEntity<TestEntity>();
			DefaultParticleSystem* particleSystem = entity->AttachComponent<DefaultParticleSystem>(100);

			for (u32 i = 0; i < 10; i++)
			{
				particleSystem->Emit({.Duration = 5.0f});
			}

			particleSystem->UseDefaultMaterial();

			MockEntityManager::s_Renderable = particleSystem;

			EXPECT_EQ(MockRenderBackend::s_UseProgramCalls, 0);
			EXPECT_EQ(MockRenderBackend::s_DrawElementsInstancedCalls, 0);
		}

		if (frame == 2)
		{
			EXPECT_TRUE(MockEntityManager::s_WasRendered);
			EXPECT_EQ(MockRenderBackend::s_UseProgramCalls, 1);
			EXPECT_EQ(MockRenderBackend::s_DrawElementsInstancedCalls, 1);

			EndTest();
		}
	}
}
END_GAME_TEST()
