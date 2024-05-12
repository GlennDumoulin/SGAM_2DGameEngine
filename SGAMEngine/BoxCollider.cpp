#include <vector>

#include "BoxCollider.h"

using namespace sgam;

BoxCollider::BoxCollider(GameObject* pOwner)
	: Component(pOwner)
{
	// Add the collider
	PhysicsManager::GetInstance().AddCollider(this);
}

BoxCollider::~BoxCollider()
{
	// Remove the collider
	PhysicsManager::GetInstance().RemoveCollider(this);
}

void BoxCollider::Hit(const CollisionInfo& collisionInfo)
{
	// Add the other collider to list of frame collisions
	m_FrameCollisions.insert(collisionInfo.pOther);

	// Check if the collisions just started
	if (!m_Collisions.contains(collisionInfo.pOther))
	{
		// Add the other collider to list of collision
		m_Collisions.insert(collisionInfo.pOther);

		// Notify OnCollisionEnter
		OnCollisionEnter->Notify(CollisionEvent{ collisionInfo });
	}

	// Notify OnCollision
	OnCollision->Notify(CollisionEvent{ collisionInfo });
}

void BoxCollider::Update()
{
	std::vector<BoxCollider*> collidersToErase{};

	for (BoxCollider* pCollider : m_Collisions)
	{
		// Check if the ongoing collision didn't happen during this frame
		if (!m_FrameCollisions.contains(pCollider))
		{
			// Notify OnCollisionExit
			OnCollisionExit->Notify(CollisionEvent{ CollisionInfo{ this, pCollider } });

			// Add collider to list of colliders to erase
			collidersToErase.push_back(pCollider);
		}
	}

	// Erase colliders that exited the collision
	for (BoxCollider* pCollider : collidersToErase)
	{
		m_Collisions.erase(pCollider);
	}

	// Reset the frame collisions
	m_FrameCollisions.clear();
}
