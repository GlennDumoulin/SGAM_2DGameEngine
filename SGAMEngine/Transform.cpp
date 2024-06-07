#include <stdexcept>

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
	if (m_HasPositionChanged) UpdateWorldPosition();

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
	m_HasPositionChanged = false;
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

	// Calculate and set new local pos
	const glm::vec2 newLocalPos{ pos - pParent->GetTransform()->GetWorldPosition() };
	SetLocalPosition(newLocalPos);
}

void Transform::SetPositionDirty()
{
	// Set own HasChanged
	m_HasPositionChanged = true;

	// Set children's HasChanged
	const auto& pOwner{ GetOwner() };

	const unsigned int childCount{ static_cast<unsigned int>(pOwner->GetChildCount()) };
	for (unsigned int idx{ 0 }; idx < childCount; ++idx)
	{
		const auto& pChildTransform{ pOwner->GetChildAt(idx)->GetTransform() };

		if (pChildTransform) pChildTransform->SetPositionDirty();
	}
}

void Transform::SetLocalRotation(const float rot)
{
	// Don't update if nothing changed
	if (m_LocalRotation == rot) return;

	m_LocalRotation = rot;

	SetRotationDirty();
}

void Transform::Rotate(const float deg)
{
	// Don't update if nothing changed
	if (deg == 0.0f) return;

	m_LocalRotation += deg;

	SetRotationDirty();
}

const float& Transform::GetWorldRotation()
{
	// Update if the world rotation has changed
	if (m_HasRotationChanged) UpdateWorldRotation();

	return m_WorldRotation;
}

void Transform::SetWorldRotation(const float rot)
{
	const auto& pParent{ GetParent() };

	// Check if we have a parent, if not world rot == local rot
	if (!pParent)
	{
		SetLocalRotation(rot);
		return;
	}

	// Calculate and set new local rot
	const float newLocalRot{ rot - pParent->GetTransform()->GetWorldRotation() };
	SetLocalRotation(newLocalRot);
}

void Transform::SetRotationDirty()
{
	// Set own HasChanged
	m_HasRotationChanged = true;

	// Set children's HasChanged
	const auto& pOwner{ GetOwner() };

	const unsigned int childCount{ static_cast<unsigned int>(pOwner->GetChildCount()) };
	for (unsigned int idx{ 0 }; idx < childCount; ++idx)
	{
		const auto& pChildTransform{ pOwner->GetChildAt(idx)->GetTransform() };

		if (pChildTransform) pChildTransform->SetRotationDirty();
	}
}

void Transform::UpdateWorldRotation()
{
	const auto& pParent{ GetParent() };

	// If there is no parent, use the local rotation
	if (!pParent)
	{
		m_WorldRotation = m_LocalRotation;
		return;
	}

	// Calculate the world rotation
	m_WorldRotation = pParent->GetTransform()->GetWorldRotation() + m_LocalRotation;

	// Reset HasChanged to false
	m_HasRotationChanged = false;
}

void Transform::SetLocalScale(const glm::vec2& scale)
{
	// Don't update if nothing changed
	if (m_LocalScale == scale) return;

	// Check for 0 scale
	if (scale.x == 0 || scale.y == 0)
	{
		throw std::runtime_error("Can't set scale equal to 0!");
	}

	m_LocalScale = scale;

	SetScaleDirty();
}

void Transform::Scale(const glm::vec2& multiplier)
{
	// Don't update if nothing changed
	if (multiplier == glm::vec2{ 1.f, 1.f }) return;

	// Check for 0 scale
	if (multiplier.x == 0 || multiplier.y == 0)
	{
		throw std::runtime_error("Can't set scale equal to 0!");
	}

	m_LocalScale *= multiplier;

	SetScaleDirty();
}

const glm::vec2& Transform::GetWorldScale()
{
	// Update if the world scale has changed
	if (m_HasScaleChanged) UpdateWorldScale();

	return m_WorldScale;
}

void Transform::UpdateWorldScale()
{
	const auto& pParent{ GetParent() };

	// If there is no parent, use the local scale
	if (!pParent)
	{
		m_WorldScale = m_LocalScale;
		return;
	}

	// Calculate the world scale
	m_WorldScale = pParent->GetTransform()->GetWorldScale() * m_LocalScale;

	// Reset HasChanged to false
	m_HasScaleChanged = false;
}

void Transform::SetWorldScale(const glm::vec2& scale)
{
	// Check for 0 scale
	if (scale.x == 0 || scale.y == 0)
	{
		throw std::runtime_error("Can't set scale equal to 0!");
	}

	const auto& pParent{ GetParent() };

	// Check if we have a parent, if not world scale == local scale
	if (!pParent)
	{
		SetLocalScale(scale);
		return;
	}

	// Calculate and set new local scale
	const glm::vec2 newLocalScale{ scale / pParent->GetTransform()->GetWorldScale() };
	SetLocalScale(newLocalScale);
}

void Transform::SetScaleDirty()
{
	// Set own HasChanged
	m_HasScaleChanged = true;

	// Set children's HasChanged
	const auto& pOwner{ GetOwner() };

	const unsigned int childCount{ static_cast<unsigned int>(pOwner->GetChildCount()) };
	for (unsigned int idx{ 0 }; idx < childCount; ++idx)
	{
		const auto& pChildTransform{ pOwner->GetChildAt(idx)->GetTransform() };

		if (pChildTransform) pChildTransform->SetScaleDirty();
	}
}
