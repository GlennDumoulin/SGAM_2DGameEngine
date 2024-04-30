#include "PlayerComponent.h"
#include "Events.h"
#include "ServiceLocator.h"

using namespace digdug;

void PlayerComponent::KillPlayer()
{
	--m_Health;

	// Play player hit sound
	sgam::ServiceLocator::GetSoundSystem().LoadAndPlay(m_PlayerHitSoundFile, 1.0f);

	OnPlayerDied->Notify(EntityDieEvent(GetOwner()));
}

void PlayerComponent::KillEnemy() const
{
	OnEnemyKilled->Notify(EntityDieEvent(nullptr));
}
