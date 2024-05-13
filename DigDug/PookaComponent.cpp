#include "PookaComponent.h"
#include "PookaWanderState.h"

using namespace digdug;

PookaComponent::PookaComponent(sgam::GameObject* pOwner)
	: sgam::FunctionalComponent(pOwner)
{
	// Set the initial state
	SetState(std::make_unique<PookaWanderState>(GetOwner()));
}

void PookaComponent::Update()
{
	// Update the current state
	std::unique_ptr<State> newState{ m_State->Update() };

	// Change current state, if there is a new one
	if (newState) SetState(std::move(newState));
}

void PookaComponent::SetState(std::unique_ptr<State> newState)
{
	if (m_State) m_State->OnExit();
	m_State = std::move(newState);
	m_State->OnEnter();
}
