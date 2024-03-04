#include "RotaterComponent.h"
#include "Transform.h"
#include "Time.h"

using namespace sgam;

void RotaterComponent::Update()
{
	// Calculate the new angle
	m_CurrentAngle += m_RotateSpeed * Time::GetInstance().Delta();
	
	// Calculate new position
	const float x{ cosf(m_CurrentAngle) * m_RotateRadius };
	const float y{ sinf(m_CurrentAngle) * m_RotateRadius };

	// Set new position
	GetTransform()->SetLocalPosition(x, y);
}
