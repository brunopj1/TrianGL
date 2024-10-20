#pragma once

#include "Core/Internal/Macros/TestMacros.h"
#include <Core/DataTypes.h>
#include <Core/Service.h>
#include <chrono>

namespace TGL
{
	class Clock : public Service<Clock> // NOLINT(CppClassCanBeFinal)
	{
	private:
		friend class Application;
		friend class ServiceCollection;
		friend struct ServiceDeleter<Clock>;

	protected:
		f32 m_TotalTime = 0.0f;
		f32 m_DeltaTime = 0.0f;

		u32 m_TotalFrameCount = 0;
		u32 m_SecondFrameCount = 0;
		u32 m_FrameRate = 1;

		f32 m_NextSecond = 1.0f;
		bool m_IsNewSecond = false;

	protected:
		std::chrono::steady_clock::time_point m_StartTime;
		std::chrono::steady_clock::time_point m_LastFrameTime;

	protected:
		Clock() = default;
		MOCKABLE_DESTRUCTOR ~Clock() = default;

	public:
		MOCKABLE_METHOD f32 GetTotalTime() const;
		MOCKABLE_METHOD f32 GetDeltaTime() const;

		MOCKABLE_METHOD u32 GetFrameCount() const;
		MOCKABLE_METHOD u32 GetFrameRate() const;

		MOCKABLE_METHOD bool IsNewSecond() const;

	protected:
		MOCKABLE_METHOD void Start();

	protected:
		MOCKABLE_METHOD void Update();

	protected:
		MOCKABLE_METHOD std::chrono::steady_clock::time_point CalculateCurrentTime() const;
	};
}
