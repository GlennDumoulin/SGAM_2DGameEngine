#include "PookaWanderState.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "SGAMTime.h"
#include "PookaGhostState.h"

using namespace digdug;

PookaWanderState::PookaWanderState(sgam::GameObject* pOwner)
	: m_pOwner{ pOwner }
{
}

std::unique_ptr<State> PookaWanderState::Update()
{
	// Update remaining wander time
	m_WanderTime -= sgam::Time::GetInstance().Delta();

	// Check if we should become a ghost
	if (m_WanderTime <= 0.f) return std::make_unique<PookaGhostState>(m_pOwner);

	return nullptr;
}

void PookaWanderState::OnEnter()
{
	// Set the wander texture
	const auto& pTexture{ sgam::ResourceManager::GetInstance().LoadTexture("Pooka/Default.png") };
	m_pOwner->GetComponent<sgam::TextureComponent>()->SetTexture(pTexture);

	// Get a random wander time
	m_WanderTime = static_cast<float>(rand() % (m_MaxWanderTime - m_MinWanderTime)) + static_cast<float>(m_MinWanderTime);
}

void PookaWanderState::OnExit()
{
}
