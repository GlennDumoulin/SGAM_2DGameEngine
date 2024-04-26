#include "RotaterComponent.h"
#include "Transform.h"
#include "SGAMTime.h"

using namespace sgam;

void RotaterComponent::Update()
{
	// Calculate the new angle
	m_CurrentAngle += m_RotateSpeed * Time::GetInstance().Delta();

	// Check if the angle is bigger than a full rotation
	if (m_CurrentAngle > m_FullRotation) m_CurrentAngle -= m_FullRotation;
	
	// Calculate new position
	const float x{ cosf(m_CurrentAngle) * m_RotateRadius };
	const float y{ sinf(m_CurrentAngle) * m_RotateRadius };

	// Set new position
	GetTransform()->SetLocalPosition(x, y);
}
