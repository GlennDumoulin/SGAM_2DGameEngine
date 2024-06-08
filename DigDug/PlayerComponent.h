#pragma once
#include <string>

#include "FunctionalComponent.h"
#include "Subject.h"
#include "Observer.h"

namespace digdug
{
	class PlayerComponent final : public sgam::FunctionalComponent, public sgam::Observer
	{
	public:
		void Init(int playerIdx);

		void KillPlayer();
		void KillEnemy() const;

		int GetHealth() const { return m_Health; }
		int GetPlayerIdx() const { return m_PlayerIdx; }
		int GetControllerIdx() const { return m_ControllerIdx; }

		virtual void OnNotify(const sgam::Event& event) override;

		explicit PlayerComponent(sgam::GameObject* pOwner) : sgam::FunctionalComponent(pOwner) {}
		~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		std::unique_ptr<sgam::Subject> OnPlayerDied{ std::make_unique<sgam::Subject>() };
		std::unique_ptr<sgam::Subject> OnEnemyKilled{ std::make_unique<sgam::Subject>() };

	private:
		int m_PlayerIdx{ -1 };
		int m_ControllerIdx{ -1 };

		int m_Health{ 3 };

		const std::string m_PlayerHitSoundFile{ "Sounds/PlayerHit.wav" };
	};
}
