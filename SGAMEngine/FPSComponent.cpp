#include <iostream>

#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "SGAMTime.h"

using namespace sgam;

void FPSComponent::Update()
{
	// Check if the owning GameObject has a TextComponent
	if (!m_pText)
	{
		m_pText = GetOwner()->GetComponent<TextComponent>();

		if (!m_pText)
		{
			std::cout << "FPSComponent can't render without TextComponent\n";
			return;
		}
	}

	const float deltaTime{ Time::GetInstance().Delta() };

	// Update elapsed variables and check if we have to update the FPS text
	m_ElapsedSeconds += deltaTime;
	++m_ElapsedUpdates;

	if (m_ElapsedSeconds >= m_SecondsPerUpdate)
	{
		// Calculate current FPS and update the text
		const float fps{ m_ElapsedUpdates / m_ElapsedSeconds };
		m_pText->SetText(std::format("{:.1f} FPS", fps));

		// Reset elapsed variables
		m_ElapsedSeconds = 0.0f;
		m_ElapsedUpdates = 0;
	}
}
