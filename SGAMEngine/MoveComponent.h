#pragma once
#include <glm/glm.hpp>

#include "FunctionalComponent.h"

namespace sgam
{
	class MoveComponent final : public FunctionalComponent
	{
	public:
		virtual void Update() override;

		void SetMovementSpeed(const float newSpeed) { m_MoveSpeed = newSpeed; }

		void AddMovement(const glm::vec2& direction);

		explicit MoveComponent(GameObject* pOwner) : FunctionalComponent(pOwner) {}
		~MoveComponent() = default;
		MoveComponent(const MoveComponent& other) = delete;
		MoveComponent(MoveComponent&& other) = delete;
		MoveComponent& operator=(const MoveComponent& other) = delete;
		MoveComponent& operator=(MoveComponent&& other) = delete;

	private:
		float m_MoveSpeed{ 10.f };

		glm::vec2 m_Direction{ 0.f, 0.f };
	};
}
