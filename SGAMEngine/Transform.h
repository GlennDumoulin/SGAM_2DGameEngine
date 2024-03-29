#pragma once
#include <glm/glm.hpp>

#include "Component.h"

namespace sgam
{
	class Transform final : public Component
	{
	public:
		const glm::vec2& GetLocalPosition() const { return m_LocalPosition; };
		void SetLocalPosition(const glm::vec2& pos);
		void SetLocalPosition(const float x, const float y) { SetLocalPosition(glm::vec2{ x, y }); }
		void Translate(const glm::vec2& offset);
		void Translate(const float offsetX, const float offsetY) { Translate(glm::vec2{ offsetX, offsetY }); }

		const glm::vec2& GetWorldPosition();
		void SetWorldPosition(const glm::vec2& pos);
		void SetWorldPosition(const float x, const float y) { SetWorldPosition(glm::vec2{ x, y }); }

		void SetPositionDirty();

		explicit Transform(GameObject* pOwner) : Component(pOwner) {}
		~Transform() = default;
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

	private:
		void UpdateWorldPosition();

		glm::vec2 m_LocalPosition{};
		glm::vec2 m_WorldPosition{};

		bool m_HasChanged{ true };
	};
}
