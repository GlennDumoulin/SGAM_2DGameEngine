#pragma once
#include "TextComponent.h"

namespace sgam
{
	class FPSComponent final : public TextComponent
	{
	public:
		virtual void Update() override;

		FPSComponent() = default;
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

	private:
		float m_ElapsedSeconds{};
		const float m_SecondsPerUpdate{ 0.2f };
	};
}

