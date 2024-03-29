#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

using namespace sgam;

GameObject* Component::GetParent() const
{
	// Make sure that there is an owning GameObject
	if (!m_pOwner) return nullptr;

	// Get the parent from the owning GameObject
	return m_pOwner->GetParent();
}

Transform* Component::GetTransform() const
{
	// Make sure that there is an owning GameObject
	if (!m_pOwner) return nullptr;

	// Get the transform from the owning GameObject
	return m_pOwner->GetTransform();
}
