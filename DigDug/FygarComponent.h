#pragma once
#include "FunctionalComponent.h"

namespace digdug
{
	class FygarComponent final : public sgam::FunctionalComponent
	{
	public:
		explicit FygarComponent(sgam::GameObject* pOwner);
		~FygarComponent() = default;
		FygarComponent(const FygarComponent& other) = delete;
		FygarComponent(FygarComponent&& other) = delete;
		FygarComponent& operator=(const FygarComponent& other) = delete;
		FygarComponent& operator=(FygarComponent&& other) = delete;

		virtual void Update() override;

	private:
		//...
	};
}
