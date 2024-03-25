#include <iostream>
#include <format>

#include "ScoreComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Events.h"

using namespace sgam;

void ScoreComponent::Update()
{
	// Don't update if nothing changed
	if (!m_HasChanged) return;

	// Update the score
	UpdateScore();

	// Reset hasChanged back to false
	m_HasChanged = false;
}

void ScoreComponent::UpdateScore()
{
	// Check if there is a TextComponent on the owning GameObject, if not don't update
	if (!m_pTextComponent)
	{
		m_pTextComponent = GetOwner()->GetComponent<TextComponent>();

		if (!m_pTextComponent)
		{
			std::cout << "ScoreComponent can't render without TextComponent\n";
			return;
		}
	}

	// Update the score on the TextComponent
	m_pTextComponent->SetText(std::format("Score: {}", m_Score));
}

void ScoreComponent::OnNotify(const Event& event)
{
	// Check if we were notified by an EntityDieEvent
	if (auto entityDieEvent{ dynamic_cast<const EntityDieEvent*>(&event) })
	{
		// Check if the event is valid (doesn't contain an entity)
		if (!entityDieEvent->pEntity)
		{
			m_Score += 50;
			m_HasChanged = true;

			OnScoreChanged->Notify(ScoreChangedEvent(m_Score));
		}
	}
}
