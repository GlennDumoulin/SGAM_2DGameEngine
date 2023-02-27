#pragma once
#include <chrono>
#include "Singleton.h"

using namespace std::chrono;

namespace sgam
{
	class Time final : public Singleton<Time>
	{
	public:
		void Update();

		float Delta();
		float TotalElapsed();

		int FPS();

		float FixedTimeStep();
		int MaxSubsteps();

	private:
		friend class Singleton<Time>;
		Time() = default;

		high_resolution_clock::time_point m_PrevFrameTime{ high_resolution_clock::now() };
		float m_Delta{};
		float m_TotalElapsed{};

		const float m_FixedTimeStep{ 1.f / 60 }; //60fps
		const int m_MaxSubsteps{ 6 };
	};
}
