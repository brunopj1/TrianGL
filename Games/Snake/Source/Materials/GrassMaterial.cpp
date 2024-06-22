#include "GrassMaterial.h"

#include "Util/RandomNumberGenerator.h"

using namespace TGL;

GrassMaterial::GrassMaterial()
    : Material("Assets/Shaders/grass.vert", "Assets/Shaders/grass.frag")
{
    Seed->Value = RandomNumberGenerator().GetFloat(0, 99999.999f);
}
