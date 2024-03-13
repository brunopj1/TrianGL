#include "IdGenerator.h"

using namespace TGL;

uint64_t IdGenerator::NextId()
{
    return m_NextId++;
}

void IdGenerator::Reset()
{
    m_NextId = 1;
}
