#pragma once
#include "FunctionalComponent.h"
#include "Subject.h"

namespace sgam
{
	class PlayerComponent final : public FunctionalComponent
	{
	public:
		void KillPlayer();
		void KillEnemy() const;

		int GetHealth() const { return m_Health; }

		explicit PlayerComponent(GameObject* pOwner) : FunctionalComponent(pOwner) {}
		~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		std::unique_ptr<Subject> OnPlayerDied{ std::make_unique<Subject>() };
		std::unique_ptr<Subject> OnEnemyKilled{ std::make_unique<Subject>() };

	private:
		int m_Health{ 3 };
	};
}
