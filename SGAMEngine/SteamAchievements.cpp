#include "SteamAchievements.h"
#include "isteamuserstats.h"

using namespace sgam;

void SteamAchievements::Init(const std::vector<Achievement_t>& achievements, bool shouldReset)
{
	m_Achievements = achievements;

	if (shouldReset)
	{
		for (const auto& achievement : m_Achievements)
		{
			SteamUserStats()->ClearAchievement(achievement.m_pchAchievementID);
		}
	}
}

void SteamAchievements::SetAchievement(unsigned int achievementIdx)
{
	auto pUserStats{ SteamUserStats() };
	pUserStats->SetAchievement(m_Achievements[achievementIdx].m_pchAchievementID);
	pUserStats->StoreStats();
}
