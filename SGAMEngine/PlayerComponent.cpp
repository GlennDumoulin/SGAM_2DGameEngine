#include "PlayerComponent.h"
#include "Events.h"

using namespace sgam;

void PlayerComponent::KillPlayer()
{
	--m_Health;

	OnPlayerDied->Notify(EntityDieEvent(GetOwner()));
}

void PlayerComponent::KillEnemy() const
{
	OnEnemyKilled->Notify(EntityDieEvent(nullptr));
}
