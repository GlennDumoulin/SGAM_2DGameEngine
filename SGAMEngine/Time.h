#pragma once
#include <chrono>

#include "Singleton.h"

using namespace std::chrono;

namespace sgam
{
	class Time final : public Singleton<Time>
	{
	public:
		void Init();
		void Update();
		const nanoseconds SleepTime() const;
		
		const float Delta() const { return m_Delta; }
		const float TotalElapsed() const { return m_TotalElapsed; }

		const float FixedTimeStep() const { return m_FixedTimeStep; }
		const int MaxSubsteps() const { return m_MaxSubsteps; }

		~Time() = default;
		Time(const Time& other) = delete;
		Time(Time&& other) = delete;
		Time& operator=(const Time& other) = delete;
		Time& operator=(Time&& other) = delete;

	private:
		friend class Singleton<Time>;
		Time() = default;

		high_resolution_clock::time_point m_PrevFrameTime{};
		float m_Delta{ 0.0f };
		float m_TotalElapsed{ 0.0f };

		const int m_DesiredFPS{ 60 };
		const float m_FixedTimeStep{ 0.01667f }; // ~60fps
		const int m_MaxSubsteps{ 6 };

		constexpr int DesiredFrameTimeMillies() const { return static_cast<int>(1000.0f / m_DesiredFPS); }
	};
}
