#include "Memory/SharedPtr.h"

#include "Assets/Material.h"
#include "Game/Component.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

// Helper classes
namespace
{
	class TestMaterial : public Material
	{
	public:
		static inline u32 s_LoadedMaterials = 0;

		TestMaterial()
			: Material("Assets/Shaders/test.vert", "Assets/Shaders/test.frag")
		{
			s_LoadedMaterials++;
		}

		~TestMaterial() override
		{
			s_LoadedMaterials--;
		}
	};

	class OtherTestMaterial final : public TestMaterial
	{
	public:
		OtherTestMaterial() = default;
		~OtherTestMaterial() override = default;
	};
}

// Tests

BEGIN_GAME_TEST(SharedPtr, Lifetime)
{
	void OnUpdate(f32 deltaTime) override
	{
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 0);

		SharedPtr<TestMaterial> sharedPtr1 = Material::CreateInstanceOf<TestMaterial>();
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 1);
		EXPECT_NE(sharedPtr1.Get(), nullptr);

		{
			const SharedPtr<TestMaterial> sharedPtr2 = sharedPtr1; // NOLINT(performance-unnecessary-copy-initialization)
			EXPECT_EQ(TestMaterial::s_LoadedMaterials, 1);
			EXPECT_EQ(sharedPtr2.Get(), sharedPtr1.Get());
		}

		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 1);
		EXPECT_NE(sharedPtr1.Get(), nullptr);

		{
			const SharedPtr<TestMaterial> sharedPtr3 = Material::CreateInstanceOf<TestMaterial>();
			EXPECT_EQ(TestMaterial::s_LoadedMaterials, 2);
			EXPECT_NE(sharedPtr3.Get(), nullptr);
		}

		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 1);

		sharedPtr1 = nullptr;
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 0);
		EXPECT_EQ(sharedPtr1.Get(), nullptr);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(SharedPtr, ImplicitConversion)
{
	void OnUpdate(f32 deltaTime) override
	{
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 0);

		SharedPtr<TestMaterial> sharedPtr1 = Material::CreateInstanceOf<TestMaterial>();
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 1);
		EXPECT_NE(sharedPtr1.Get(), nullptr);

		SharedPtr<Material> sharedPtr2 = sharedPtr1;
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 1);
		EXPECT_EQ(sharedPtr1.Get(), sharedPtr1.Get());

		sharedPtr1 = nullptr;
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 1);
		EXPECT_EQ(sharedPtr1.Get(), nullptr);
		EXPECT_NE(sharedPtr2.Get(), nullptr);

		sharedPtr2 = nullptr;
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 0);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(SharedPtr, CastTo)
{
	void OnUpdate(f32 deltaTime) override
	{
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 0);

		SharedPtr<TestMaterial> sharedPtr1 = Material::CreateInstanceOf<OtherTestMaterial>();
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 1);
		EXPECT_NE(sharedPtr1.Get(), nullptr);

		SharedPtr<Material> sharedPtr2 = CastTo<Material>(sharedPtr1);
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 1);
		EXPECT_EQ(sharedPtr2.Get(), sharedPtr1.Get());

		SharedPtr<OtherTestMaterial> sharedPtr3 = CastTo<OtherTestMaterial>(sharedPtr1);
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 1);
		EXPECT_EQ(sharedPtr3.Get(), sharedPtr1.Get());

		SharedPtr<Texture> sharedPtr4 = CastTo<Texture>(sharedPtr1);
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 1);
		EXPECT_EQ(sharedPtr4.Get(), nullptr);

		sharedPtr1 = nullptr;
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 1);
		EXPECT_EQ(sharedPtr1.Get(), nullptr);
		EXPECT_NE(sharedPtr2.Get(), nullptr);
		EXPECT_NE(sharedPtr3.Get(), nullptr);
		EXPECT_EQ(sharedPtr4.Get(), nullptr);

		sharedPtr2 = nullptr;
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 1);
		EXPECT_EQ(sharedPtr1.Get(), nullptr);
		EXPECT_EQ(sharedPtr2.Get(), nullptr);
		EXPECT_NE(sharedPtr3.Get(), nullptr);
		EXPECT_EQ(sharedPtr4.Get(), nullptr);

		sharedPtr3 = nullptr;
		EXPECT_EQ(TestMaterial::s_LoadedMaterials, 0);
		EXPECT_EQ(sharedPtr1.Get(), nullptr);
		EXPECT_EQ(sharedPtr2.Get(), nullptr);
		EXPECT_EQ(sharedPtr3.Get(), nullptr);
		EXPECT_EQ(sharedPtr4.Get(), nullptr);

		EndTest();
	}
}
END_GAME_TEST()
