#include "Object.h"

using namespace TGL;

Object::Object(const bool shouldUpdate)
    : m_ShouldUpdate(shouldUpdate)
{}

int Object::GetOrderOfExecution() const
{
    return 0;
}

void Object::OnStart()
{}

void Object::OnUpdate(const float deltaTime)
{}
