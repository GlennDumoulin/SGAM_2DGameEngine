#pragma once
#include <glm/glm.hpp>

#include "Component.h"

namespace sgam
{
	class Transform final : public Component
	{
	public:
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z);

		Transform() = default;
		~Transform() = default;
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

	private:
		glm::vec3 m_position{};
	};
}
