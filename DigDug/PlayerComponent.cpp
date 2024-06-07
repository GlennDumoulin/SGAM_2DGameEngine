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

	//TEMP --> Add player states, state binds needed input commands
	// Bind input commands
	BindInputs();

	//TEMP --> Add player states, state sets needed texture
	auto pTextureComp{ GetOwner()->GetComponent<sgam::TextureComponent>() };
	if (pTextureComp)
	{
		std::string texturePath{ std::format("DigDug{}/Walking.png", m_PlayerIdx) };
		const auto& pTexture{ sgam::ResourceManager::GetInstance().LoadTexture(texturePath) };
		pTextureComp->SetTexture(pTexture);
	}
}

void PlayerComponent::BindInputs() const
{
	// Bind keyboard inputs for first player
	if (m_PlayerIdx == 0) BindKeyboardInputs();

	// Bind controller inputs for all players
	BindControllerInputs();
}

void PlayerComponent::BindKeyboardInputs() const
{
	//...
}

void PlayerComponent::BindControllerInputs() const
{
	//...
}

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
