#pragma once
#include <vector>

#include "Singleton.h"
#include "Achievement.h"

namespace sgam
{
	class SteamAchievements final : public Singleton<SteamAchievements>
	{
	public:
		enum class Achievement
		{
			ACH_WIN_ONE_GAME = 0
		};

		void Init(const std::vector<Achievement_t>& achievements, bool shouldReset = false);

		void SetAchievement(unsigned int achievementIdx);

		~SteamAchievements() = default;
		SteamAchievements(const SteamAchievements& other) = delete;
		SteamAchievements(SteamAchievements&& other) = delete;
		SteamAchievements& operator=(const SteamAchievements& other) = delete;
		SteamAchievements& operator=(SteamAchievements&& other) = delete;

	private:
		friend class Singleton<SteamAchievements>;
		SteamAchievements() = default;

		std::vector<Achievement_t> m_Achievements{};
	};
}
