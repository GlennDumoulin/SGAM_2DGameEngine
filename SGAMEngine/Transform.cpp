#include "Transform.h"
#include "GameObject.h"

using namespace sgam;

void Transform::SetLocalPosition(const glm::vec2& pos)
{
	// Don't update if nothing changed
	if (m_LocalPosition == pos) return;

	m_LocalPosition = pos;

	SetPositionDirty();
}

void Transform::Translate(const glm::vec2& offset)
{
	// Don't update if nothing changed
	if (offset == glm::vec2{ 0.f, 0.f }) return;

	m_LocalPosition += offset;

	SetPositionDirty();
}

const glm::vec2& Transform::GetWorldPosition()
{
	// Update if the world position has changed
	if (m_HasChanged) UpdateWorldPosition();

	return m_WorldPosition;
}

void Transform::UpdateWorldPosition()
{
	const auto& pParent{ GetParent() };

	// If there is no parent, use the local position
	if (!pParent)
	{
		m_WorldPosition = m_LocalPosition;
		return;
	}

	// Calculate the world position
	m_WorldPosition = pParent->GetTransform()->GetWorldPosition() + m_LocalPosition;

	// Reset HasChanged to false
	m_HasChanged = false;
}

void Transform::SetWorldPosition(const glm::vec2& pos)
{
	const auto& pParent{ GetParent() };

	// Check if we have a parent, if not world pos == local pos
	if (!pParent)
	{
		SetLocalPosition(pos);
		return;
	}

	const glm::vec2 newLocalPos{ pos - pParent->GetTransform()->GetWorldPosition() };

	// Don't update if nothing changed
	if (m_LocalPosition == newLocalPos) return;

	m_LocalPosition = newLocalPos;

	SetPositionDirty();
}

void Transform::SetPositionDirty()
{
	// Set own HasChanged
	m_HasChanged = true;

	// Set children's HasChanged
	const auto& pOwner{ GetOwner() };

	const unsigned int childCount{ static_cast<unsigned int>(pOwner->GetChildCount()) };
	for (unsigned int idx{ 0 }; idx < childCount; ++idx)
	{
		const auto& pChildTransform{ pOwner->GetChildAt(idx)->GetTransform() };

		if (pChildTransform) pChildTransform->SetPositionDirty();
	}
}
