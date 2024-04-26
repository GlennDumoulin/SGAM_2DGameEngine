#include "SGAMTime.h"

namespace sgam
{
	void Time::Init()
	{
		// Set the initial time
		m_PrevFrameTime = high_resolution_clock::now();
	}

	void Time::Update()
	{
		// Get the current time
		const auto currentTime{ high_resolution_clock::now() };

		// Update the delta time and total elapsed time
		m_Delta = duration<float>(currentTime - m_PrevFrameTime).count();
		m_TotalElapsed += m_Delta;
		
		// Replace the previous frame time with the current time
		m_PrevFrameTime = currentTime;
	}

	const nanoseconds Time::SleepTime() const
	{
		// Calculate the sleep time for the next frame
		const auto sleepTime{ m_PrevFrameTime + milliseconds(DesiredFrameTimeMillies()) - high_resolution_clock::now() };

		return sleepTime;
	}
}
