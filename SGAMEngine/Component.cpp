#include "Component.h"
#include "GameObject.h"

using namespace sgam;

Transform* Component::GetTransform() const
{
	// Make sure that there is an owning GameObject
	if (!m_pOwner) return nullptr;

	// Get the transform from the owning GameObject
	return m_pOwner->GetTransform();
}
