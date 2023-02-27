#include "Time.h"

namespace sgam
{
	void Time::Update()
	{
		const auto currentTime{ high_resolution_clock::now() };

		m_Delta = duration_cast<duration<float>>(currentTime - m_PrevFrameTime).count();
		m_PrevFrameTime = currentTime;
		m_TotalElapsed += m_Delta;
	}

	float Time::Delta()
	{
		return m_Delta;
	}
	float Time::TotalElapsed()
	{
		return m_TotalElapsed;
	}

	int Time::FPS()
	{
		return static_cast<int>(1 / m_Delta);
	}

	float Time::FixedTimeStep()
	{
		return m_FixedTimeStep;
	}
	int Time::MaxSubsteps()
	{
		return m_MaxSubsteps;
	}
}
