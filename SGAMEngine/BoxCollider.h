#pragma once
#include <set>

#include "Component.h"
#include "Subject.h"
#include "CollisionData.h"
#include "PhysicsManager.h"

namespace sgam
{
	class BoxCollider final : public Component
	{
	public:
		explicit BoxCollider(GameObject* pOwner);
		~BoxCollider();
		BoxCollider(const BoxCollider& other) = delete;
		BoxCollider(BoxCollider&& other) = delete;
		BoxCollider& operator=(const BoxCollider& other) = delete;
		BoxCollider& operator=(BoxCollider&& other) = delete;

		const Rect& GetShape() const { return m_ColliderShape; }
		void SetTopLeft(const glm::vec2& topLeft) { m_ColliderShape.topLeft = topLeft; }
		void SetTopLeft(const float x, const float y) { SetTopLeft(glm::vec2{ x, y }); }
		void SetSize(const glm::ivec2& size) { m_ColliderShape.size = size; }
		void SetSize(const int width, const int height) { SetSize(glm::ivec2{ width, height }); }

		std::unique_ptr<Subject> OnCollisionEnter{ std::make_unique<Subject>() };
		std::unique_ptr<Subject> OnCollision{ std::make_unique<Subject>() };
		std::unique_ptr<Subject> OnCollisionExit{ std::make_unique<Subject>() };

	private:
		// Only the PhysicsManager should be able to trigger collisions
		friend PhysicsManager;
		void Hit(const CollisionInfo& collisionInfo);
		void Update();

		std::set<BoxCollider*> m_FrameCollisions{};
		std::set<BoxCollider*> m_Collisions{};

		Rect m_ColliderShape{};
	};
}
