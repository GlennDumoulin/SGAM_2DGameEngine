#pragma once
#include <string>

#include "FunctionalComponent.h"
#include "Subject.h"

namespace digdug
{
	class PlayerComponent final : public sgam::FunctionalComponent
	{
	public:
		void KillPlayer();
		void KillEnemy() const;

		int GetHealth() const { return m_Health; }

		explicit PlayerComponent(sgam::GameObject* pOwner) : sgam::FunctionalComponent(pOwner) {}
		~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		std::unique_ptr<sgam::Subject> OnPlayerDied{ std::make_unique<sgam::Subject>() };
		std::unique_ptr<sgam::Subject> OnEnemyKilled{ std::make_unique<sgam::Subject>() };

	private:
		int m_Health{ 3 };

		std::string m_PlayerHitSoundFile{ "PlayerHit.wav" };
	};
}
