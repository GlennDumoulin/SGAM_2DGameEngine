#pragma once
#include <glm/glm.hpp>

#include "FunctionalComponent.h"

namespace sgam
{
	class RotaterComponent final : public FunctionalComponent
	{
	public:
		virtual void Update() override;

		void SetRotateRadius(const float radius) { m_RotateRadius = radius; }
		void SetRotateSpeedDeg(const float degrees) { SetRotateSpeedRad(glm::radians(degrees)); }
		void SetRotateSpeedRad(const float rad) { m_RotateSpeed = rad; }

		RotaterComponent(GameObject* pOwner) : FunctionalComponent(pOwner) {}
		~RotaterComponent() = default;
		RotaterComponent(const RotaterComponent& other) = delete;
		RotaterComponent(RotaterComponent&& other) = delete;
		RotaterComponent& operator=(const RotaterComponent& other) = delete;
		RotaterComponent& operator=(RotaterComponent&& other) = delete;

	private:
		float m_RotateRadius{ 20.f };
		float m_RotateSpeed{ glm::radians(360.f) };
		float m_CurrentAngle{};
	};
}
