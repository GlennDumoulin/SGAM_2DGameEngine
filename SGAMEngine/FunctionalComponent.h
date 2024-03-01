#pragma once
#include "Component.h"

namespace sgam
{
	class FunctionalComponent : public Component
	{
	public:
		virtual void FixedUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};

		virtual ~FunctionalComponent() = default;
		FunctionalComponent(const FunctionalComponent& other) = delete;
		FunctionalComponent(FunctionalComponent&& other) = delete;
		FunctionalComponent& operator=(const FunctionalComponent& other) = delete;
		FunctionalComponent& operator=(FunctionalComponent&& other) = delete;

	protected:
		explicit FunctionalComponent(GameObject* pOwner) : Component(pOwner) {}
	};
}
