#include <iostream>
#include <format>

#include "ServiceLocator.h"
#include "CollisionData.h"
#include "Events.h"

#include "GameManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "PlayerComponent.h"
#include "TextureComponent.h"

#include "BoxCollider.h"

#include "PlayerWalkingState.h"

using namespace digdug;

void PlayerComponent::Init(int playerIdx)
{
	// Check if the component was already initialized
	if (m_PlayerIdx != -1)
	{
		std::cout << "PlayerComponent was already initialized!\n";
		return;
	}

	// Set player & controller idx
	m_PlayerIdx = playerIdx;

	// 1-player: always index 0
	// 2-player: player 1 has keyboard and index 1, player 2 has index 0
	m_ControllerIdx = GameManager::GetInstance().GetNrOfPlayers() - 1 - m_PlayerIdx;

	// Set the player in the GameManager
	GameManager::GetInstance().SetPlayer(this);

	// Set the initial state
	SetState(std::make_unique<PlayerWalkingState>(this));
}

void PlayerComponent::Update()
{
	// Update the current state
	std::unique_ptr<PlayerState> pNewState{ m_pState->Update() };

	// Change current state, if there is a new one
	if (pNewState) SetState(std::move(pNewState));
}

void PlayerComponent::HandleInput(const glm::vec2& movement, bool isPumping)
{
	// Handle input in the current state
	std::unique_ptr<PlayerState> pNewState{ m_pState->HandleInput(movement, isPumping) };

	// Change current state, if there is a new one
	if (pNewState) SetState(std::move(pNewState));
}

void PlayerComponent::SetState(std::unique_ptr<PlayerState> pNewState)
{
	if (m_pState) m_pState->OnExit();
	m_pState = std::move(pNewState);
	m_pState->OnEnter();
}

void PlayerComponent::AddMovement(const glm::vec2& direction)
{
	HandleInput(direction, false);
}

void PlayerComponent::SetIsPumping(bool isPumping)
{
	HandleInput(glm::vec2{}, isPumping);
}

void PlayerComponent::KillPlayer()
{
	--m_Health;
	std::cout << "Health: " << m_Health << "\n";

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
		// Get the BoxCollider we collided with
		sgam::BoxCollider* pOther{ collisionEvent->collisionInfo.pOther };

		// Ignore collisions with other players
		//TEMP --> Add layer to BoxCollider & ignoreLayers to PhysicsManager
		if (pOther->GetOwner()->GetComponent<PlayerComponent>()) return;

		// Any other collisions is an enemy in the current state of the game
		KillPlayer();
	}
}
