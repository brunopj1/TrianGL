#include "DefaultMaterial.h"

using namespace Engine::DefaultResources;

DefaultMaterial::DefaultMaterial() // TODO move these files to the engine project and copy them to the Bin directory
    : Material("Assets/Shaders/default.vert", "Assets/Shaders/default.frag", true)
{
    // TODO add attributes here (texture, color, etc)
    // TODO add attributes in the base class (PVMMatrix, etc)
}
