#include <iostream>
#include <format>

#include "LivesComponent.h"
#include "PlayerComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Events.h"

using namespace sgam;

void LivesComponent::Update()
{
	// Don't update if nothing changed
	if (!m_HasChanged) return;

	// Update the lives
	UpdateLives();

	// Reset hasChanged back to false
	m_HasChanged = false;
}

void LivesComponent::OnNotify(const Event& event)
{
	// Check if we were notified by an EntityDieEvent
	if (auto entityDieEvent{ dynamic_cast<const EntityDieEvent*>(&event) })
	{
		// Check if the event is valid (contains an entity)
		if (entityDieEvent->pEntity)
		{
			const auto& playerComp{ entityDieEvent->pEntity->GetComponent<PlayerComponent>() };

			if (!playerComp) return;

			m_Lives = playerComp->GetHealth();
			m_HasChanged = true;
		}
	}
}

void LivesComponent::UpdateLives()
{
	// Check if there is a TextComponent on the owning GameObject, if not don't update
	if (!m_pTextComponent)
	{
		m_pTextComponent = GetOwner()->GetComponent<TextComponent>();

		if (!m_pTextComponent)
		{
			std::cout << "LivesComponent can't render without TextComponent\n";
			return;
		}
	}

	// Update the lives on the TextComponent
	m_pTextComponent->SetText(std::format("Lives: {}", m_Lives));
}
