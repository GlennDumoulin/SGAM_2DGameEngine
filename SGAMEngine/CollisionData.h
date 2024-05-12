#pragma once
#include <glm/glm.hpp>

#include "Event.h"

namespace sgam
{
	class BoxCollider;

	struct Rect final
	{
		explicit Rect() = default;
		explicit Rect(const glm::vec2& topLeft, const glm::ivec2& size)
			: topLeft{ topLeft }, size{ size }
		{
		}
		explicit Rect(const glm::vec2& topLeft, const int sizeX, const int sizeY)
			: Rect(topLeft, glm::ivec2{ sizeX, sizeY })
		{
		}
		~Rect() = default;

		glm::vec2 topLeft{};
		glm::ivec2 size{};
	};

	struct CollisionInfo final
	{
		explicit CollisionInfo() = default;
		explicit CollisionInfo(BoxCollider* pCollider, BoxCollider* pOther)
			: pCollider{ pCollider }, pOther{ pOther }
		{
		}
		~CollisionInfo() = default;

		BoxCollider* pCollider{};
		BoxCollider* pOther{};
	};

	struct CollisionEvent final : public Event
	{
		explicit CollisionEvent(const CollisionInfo& collisionInfo)
			: collisionInfo{ collisionInfo }
		{
		}

		const CollisionInfo collisionInfo{};
	};
}
