#include <iostream>

#include "ServiceLocator.h"
#include "CollisionData.h"

#include "PlayerComponent.h"
#include "Events.h"

using namespace digdug;

void PlayerComponent::KillPlayer()
{
	--m_Health;

	// Play player hit sound
	sgam::ServiceLocator::GetSoundSystem().LoadAndPlay(m_PlayerHitSoundFile, .5f);

	OnPlayerDied->Notify(EntityDieEvent(GetOwner()));
}

void PlayerComponent::KillEnemy() const
{
	OnEnemyKilled->Notify(EntityDieEvent(nullptr));
}

void PlayerComponent::OnNotify(const sgam::Event& event)
{
	// Check if we were notified by a CollisionEvent
	if (auto collisionEvent{ dynamic_cast<const sgam::CollisionEvent*>(&event) })
	{
		std::cout << "Collision entered!\n";
	}
}
