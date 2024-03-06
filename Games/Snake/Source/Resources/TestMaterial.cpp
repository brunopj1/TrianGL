#include "TestMaterial.h"

#include "Resources/MaterialAttributes.h"

TestMaterial::TestMaterial()
    : Material("Assets/Shaders/test.vert", "Assets/Shaders/Test.frag", true)
{
    auto a = AddAttribute<Engine::Resources::IntMaterialAttribute>("hi");
}
