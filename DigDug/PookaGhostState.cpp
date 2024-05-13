#include "PookaGhostState.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "SGAMTime.h"
#include "PookaWanderState.h"

using namespace digdug;

PookaGhostState::PookaGhostState(sgam::GameObject* pOwner)
	: m_pOwner{ pOwner }
{
}

std::unique_ptr<State> PookaGhostState::Update()
{
	// Update remaining ghost time
	m_GhostTime -= sgam::Time::GetInstance().Delta();

	// Check if we should return to wander state
	if (m_GhostTime <= 0.f) return std::make_unique<PookaWanderState>(m_pOwner);

	return nullptr;
}

void PookaGhostState::OnEnter()
{
	// Set the ghost texture
	const auto& pTexture{ sgam::ResourceManager::GetInstance().LoadTexture("PookaGhost.png") };
	m_pOwner->GetComponent<sgam::TextureComponent>()->SetTexture(pTexture);

	// Get a random ghost time
	m_GhostTime = static_cast<float>(rand() % (m_MaxGhostTime - m_MinGhostTime)) + static_cast<float>(m_MinGhostTime);
}

void PookaGhostState::OnExit()
{
}

