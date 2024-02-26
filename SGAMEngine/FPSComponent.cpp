#include <sstream>

#include "FPSComponent.h"
#include "Time.h"

using namespace sgam;

void FPSComponent::Update()
{
	const float deltaTime{ Time::GetInstance().Delta() };

	// Update elapsedSeconds and check if we have to update the FPS text
	m_ElapsedSeconds += deltaTime;
	if (m_ElapsedSeconds >= m_SecondsPerUpdate)
	{
		m_ElapsedSeconds -= m_SecondsPerUpdate;

		// Calculate current FPS and update the text
		std::stringstream fpsText{};
		fpsText << static_cast<int>(1.0f / deltaTime);
		fpsText << " FPS";

		SetText(fpsText.str());

		// Handle updating the text texture
		TextComponent::Update();
	}
}
