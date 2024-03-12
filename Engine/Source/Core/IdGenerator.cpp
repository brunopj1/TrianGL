#include "IdGenerator.h"

using namespace TGL;

uint32_t IdGenerator::NextId()
{
    return m_NextId++;
}

void IdGenerator::Reset()
{
    m_NextId = 1;
}
