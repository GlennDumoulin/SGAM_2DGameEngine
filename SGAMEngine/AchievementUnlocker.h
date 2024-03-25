#pragma once
#include "FunctionalComponent.h"
#include "Observer.h"
#include "SteamAchievements.h"
#include "Events.h"

namespace sgam
{
	class AchievementUnlocker final : public FunctionalComponent, public Observer
	{
	public:
		virtual void OnNotify(const Event& event) override
		{
			// Check if we were notified by a ScoreChangedEvent
			if (auto scoreChangedEvent{ dynamic_cast<const ScoreChangedEvent*>(&event) })
			{
				// Check if we reached the target score
				if (scoreChangedEvent->score >= m_ScoreForAchievement)
				{
					SteamAchievements::GetInstance().SetAchievement(
						static_cast<unsigned int>(SteamAchievements::Achievement::ACH_WIN_ONE_GAME)
					);
				}
			}
		}

		AchievementUnlocker(GameObject* pOwner) : FunctionalComponent(pOwner) {}
		~AchievementUnlocker() = default;
		AchievementUnlocker(const AchievementUnlocker& other) = delete;
		AchievementUnlocker(AchievementUnlocker&& other) = delete;
		AchievementUnlocker& operator=(const AchievementUnlocker& other) = delete;
		AchievementUnlocker& operator=(AchievementUnlocker&& other) = delete;

	private:
		const unsigned int m_ScoreForAchievement{ 500 };
	};
}
