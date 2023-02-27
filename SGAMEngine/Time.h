#pragma once
#include <chrono>

using namespace std::chrono;

namespace sgam
{
	class Time final
	{
	public:
		static void Update();
		static float Delta();
		static float TotalElapsed();

	private:
		Time() = default;

		static high_resolution_clock::time_point m_PrevFrameTime;
		static float m_Delta;
		static float m_TotalElapsed;
	};
}
