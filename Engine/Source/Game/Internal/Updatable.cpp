﻿#include "Updatable.h"

using namespace Engine;

Updatable::Updatable(const bool shouldUpdate)
    : m_ShouldUpdate(shouldUpdate)
{}

int Updatable::GetOrderOfExecution() const
{
    return 0;
}

void Updatable::OnStart() {}

void Updatable::OnUpdate(float deltaTime) {}
