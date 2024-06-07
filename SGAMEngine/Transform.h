#pragma once
#include <glm/glm.hpp>

#include "Component.h"

namespace sgam
{
	class Transform final : public Component
	{
	public:
		// Position Functions
		const glm::vec2& GetLocalPosition() const { return m_LocalPosition; };
		void SetLocalPosition(const glm::vec2& pos);
		void SetLocalPosition(const float x, const float y) { SetLocalPosition(glm::vec2{ x, y }); }
		void Translate(const glm::vec2& offset);
		void Translate(const float offsetX, const float offsetY) { Translate(glm::vec2{ offsetX, offsetY }); }

		const glm::vec2& GetWorldPosition();
		void SetWorldPosition(const glm::vec2& pos);
		void SetWorldPosition(const float x, const float y) { SetWorldPosition(glm::vec2{ x, y }); }

		void SetPositionDirty();

		// Rotation Functions
		const float& GetLocalRotation() const { return m_LocalRotation; };
		void SetLocalRotation(const float rot);
		void Rotate(const float deg);

		const float& GetWorldRotation();
		void SetWorldRotation(const float rot);

		void SetRotationDirty();

		// Scale Functions
		const glm::vec2& GetLocalScale() const { return m_LocalScale; };
		void SetLocalScale(const glm::vec2& scale);
		void SetLocalScale(const float x, const float y) { SetLocalScale(glm::vec2{ x, y }); }
		void SetLocalScale(const float scale) { SetLocalScale(scale, scale); }
		void Scale(const glm::vec2& multiplier);
		void Scale(const float multiplierX, const float multiplierY) { Scale(glm::vec2{ multiplierX, multiplierY }); }
		void Scale(const float multiplier) { Scale(multiplier); }

		const glm::vec2& GetWorldScale();
		void SetWorldScale(const glm::vec2& scale);
		void SetWorldScale(const float x, const float y) { SetWorldPosition(glm::vec2{ x, y }); }
		void SetWorldScale(const float scale) { SetWorldPosition(scale, scale); }

		void SetScaleDirty();

		explicit Transform(GameObject* pOwner) : Component(pOwner) {}
		~Transform() = default;
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

	private:
		void UpdateWorldPosition();
		void UpdateWorldRotation();
		void UpdateWorldScale();

		glm::vec2 m_LocalPosition{ 0.0f, 0.0f };
		glm::vec2 m_WorldPosition{ 0.0f, 0.0f };

		float m_LocalRotation{ 0.0f };
		float m_WorldRotation{ 0.0f };

		glm::vec2 m_LocalScale{ 1.0f, 1.0f };
		glm::vec2 m_WorldScale{ 1.0f, 1.0f };

		bool m_HasPositionChanged{ true };
		bool m_HasRotationChanged{ true };
		bool m_HasScaleChanged{ true };
	};
}
