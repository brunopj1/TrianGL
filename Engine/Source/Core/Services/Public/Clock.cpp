﻿#include <Core/Services/Public/Clock.h>

using namespace TGL;

f32 Clock::GetTotalTime() const
{
	return m_TotalTime;
}

f32 Clock::GetDeltaTime() const
{
	return m_DeltaTime;
}

u32 Clock::GetFrameCount() const
{
	return m_TotalFrameCount;
}

u32 Clock::GetFrameRate() const
{
	return m_FrameRate;
}

bool Clock::IsNewSecond() const
{
	return m_IsNewSecond;
}

void Clock::Start()
{
	m_StartTime = m_LastFrameTime = std::chrono::steady_clock::now();
}

void Clock::Update()
{
	const auto currentTime = CalculateCurrentTime();

	m_DeltaTime = std::chrono::duration<f32>(currentTime - m_LastFrameTime).count();
	m_TotalTime = std::chrono::duration<f32>(currentTime - m_StartTime).count();

	m_LastFrameTime = currentTime;

	m_TotalFrameCount++;
	m_SecondFrameCount++;

	if (m_TotalTime >= m_NextSecond)
	{
		m_IsNewSecond = true;
		m_NextSecond += 1.0f;

		m_FrameRate = m_SecondFrameCount;
		m_SecondFrameCount = 0;
	}
	else
	{
		m_IsNewSecond = false;
	}
}

std::chrono::steady_clock::time_point Clock::CalculateCurrentTime() const // NOLINT(CppMemberFunctionMayBeStatic)
{
	return std::chrono::steady_clock::now();
}
