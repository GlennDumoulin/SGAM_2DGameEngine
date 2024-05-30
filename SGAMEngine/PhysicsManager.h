#pragma once
#include <vector>

#include "Singleton.h"

namespace sgam
{
	class BoxCollider;
	struct CollisionInfo;

	class PhysicsManager final : public Singleton<PhysicsManager>
	{
	public:
		void AddCollider(BoxCollider* pCollider);
		void RemoveCollider(BoxCollider* pCollider);
		void ClearColliders() { m_Colliders.clear(); }

		void Update();

		void SetCollisionEpsilon(const float newValue) { m_CollisionEpsilon = newValue; }

	private:
		friend class Singleton<PhysicsManager>;
		explicit PhysicsManager() = default;
		~PhysicsManager() = default;
		PhysicsManager(const PhysicsManager& other) = delete;
		PhysicsManager(PhysicsManager&& other) = delete;
		PhysicsManager& operator=(const PhysicsManager& other) = delete;
		PhysicsManager& operator=(PhysicsManager&& other) = delete;

		bool CheckCollision(CollisionInfo& collisionInfo) const;

		std::vector<BoxCollider*> m_Colliders{};

		float m_CollisionEpsilon{ FLT_EPSILON };
	};
}
