#include "MoveComponent.h"
#include "SGAMTime.h"
#include "Transform.h"

using namespace sgam;

void MoveComponent::Update()
{
	// Don't update if we aren't moving
	if (m_Direction == glm::vec2{} || fabs(m_MoveSpeed) <= FLT_EPSILON) return;

	// Normalize the move direction
	m_Direction = glm::normalize(m_Direction);

	// Apply movement to GameObject
	const glm::vec2 movement{ m_Direction * m_MoveSpeed * Time::GetInstance().Delta() };
	GetTransform()->Translate(movement);

	// Reset the move direction for next frame
	m_Direction = glm::vec2{};
}

void MoveComponent::AddMovement(const glm::vec2& direction)
{
	m_Direction += direction;
}
