#pragma once
#include <glm/glm.hpp>

#include "Component.h"

namespace sgam
{
	class Transform final : public Component
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);

		Transform(GameObject* pOwner) : Component(pOwner) {}
		~Transform() = default;
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

	private:
		glm::vec3 m_Position{};
	};
}
