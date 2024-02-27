#pragma once
#include "Component.h"

namespace sgam
{
	class TextComponent;

	class FPSComponent final : public Component
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
		TextComponent* m_pText{};

		const float m_SecondsPerUpdate{ 0.2f };

		float m_ElapsedSeconds{};
		int m_ElapsedUpdates{};
	};
}

