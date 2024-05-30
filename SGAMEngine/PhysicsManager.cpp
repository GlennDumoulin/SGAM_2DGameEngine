#include "PhysicsManager.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "CollisionData.h"

using namespace sgam;

void PhysicsManager::AddCollider(BoxCollider* pCollider)
{
	// Check if the collider already exists
	if (std::find(m_Colliders.begin(), m_Colliders.end(), pCollider) != m_Colliders.end()) return;

	// Add the collider
	m_Colliders.push_back(pCollider);
}

void PhysicsManager::RemoveCollider(BoxCollider* pCollider)
{
	// Check if the list is empty
	if (m_Colliders.empty()) return;

	// Remove the collider
	m_Colliders.erase(std::remove(m_Colliders.begin(), m_Colliders.end(), pCollider), m_Colliders.end());
}

void PhysicsManager::Update()
{
	const size_t collidersSize{ m_Colliders.size() };

	// Don't check collisions if there's less than 2 colliders
	if (collidersSize < 2) return;

	BoxCollider* pCurrentCollider{};
	BoxCollider* pOtherCollider{};

	// Loop over all colliders
	for (size_t idx{}; idx < collidersSize - 1; ++idx)
	{
		pCurrentCollider = m_Colliders.at(idx);

		// Don't check disabled colliders
		if (!pCurrentCollider->IsEnabled() || !pCurrentCollider->GetOwner()->IsEnabled()) continue;

		// Loop over all colliders later in the list to avoid dubble checking
		for (size_t otherIdx{ idx + 1 }; otherIdx < collidersSize; ++otherIdx)
		{
			pOtherCollider = m_Colliders.at(otherIdx);

			// Don't check disabled colliders
			if (!pOtherCollider->IsEnabled() || !pOtherCollider->GetOwner()->IsEnabled()) continue;

			// Handle collision check
			CollisionInfo collisionInfo{ pCurrentCollider, pOtherCollider };
			if (CheckCollision(collisionInfo))
			{
				// Hit collider
				pCurrentCollider->Hit(collisionInfo);

				// Swap colliders
				collisionInfo.pCollider = pOtherCollider;
				collisionInfo.pOther = pCurrentCollider;

				// Hit otherCollider
				pOtherCollider->Hit(collisionInfo);
			}
		}
	}

	// Update all colliders
	for (BoxCollider* pCollider : m_Colliders)
	{
		// Don't update disabled colliders
		if (!pCollider->IsEnabled() || !pCollider->GetOwner()->IsEnabled()) continue;

		pCollider->Update();
	}
}

bool PhysicsManager::CheckCollision(CollisionInfo& collisionInfo) const
{
	// Get collider shapes
	const Rect shape{ collisionInfo.pCollider->GetShape() };
	const glm::vec2 shapePos{ collisionInfo.pCollider->GetTransform()->GetWorldPosition() };
	const Rect otherShape{ collisionInfo.pOther->GetShape() };
	const glm::vec2 otherShapePos{ collisionInfo.pOther->GetTransform()->GetWorldPosition() };

	// Check horizontal overlap
	const float sLeft{ shapePos.x + shape.topLeft.x };
	const float sRight{ shapePos.x + shape.topLeft.x + shape.size.x };
	const float oLeft{ otherShapePos.x + otherShape.topLeft.x };
	const float oRight{ otherShapePos.x + otherShape.topLeft.x + otherShape.size.x };

	//if (sRight < oLeft + m_CollisionEpsilon || oRight < sLeft + m_CollisionEpsilon) return false;
	const float horizontalOverlap{ std::min(sRight, oRight) - std::max(sLeft, oLeft) };
	if (horizontalOverlap < m_CollisionEpsilon) return false;

	// Check vertical overlap
	const float sTop{ shapePos.y + shape.topLeft.y };
	const float sBottom{ shapePos.y + shape.topLeft.y + shape.size.y };
	const float oTop{ otherShapePos.y + otherShape.topLeft.y };
	const float oBottom{ otherShapePos.y + otherShape.topLeft.y + otherShape.size.y };

	//if (sBottom < oTop + m_CollisionEpsilon || oBottom < sTop + m_CollisionEpsilon) return false;
	const float verticalOverlap{ std::min(sBottom, oBottom) - std::max(sTop, oTop) };
	if (verticalOverlap < m_CollisionEpsilon) return false;

	// If both directions are overlapping, we have a collision
	return true;
}
