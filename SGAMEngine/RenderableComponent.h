#pragma once
#include "Component.h"

namespace sgam
{
	class RenderableComponent : public Component
	{
	public:
		virtual void Render() const {};

		virtual ~RenderableComponent() = default;
		RenderableComponent(const RenderableComponent& other) = delete;
		RenderableComponent(RenderableComponent&& other) = delete;
		RenderableComponent& operator=(const RenderableComponent& other) = delete;
		RenderableComponent& operator=(RenderableComponent&& other) = delete;

	protected:
		explicit RenderableComponent(GameObject* pOwner) : Component(pOwner) {}
	};
}
