#pragma once
#include "FunctionalComponent.h"
#include "Observer.h"

namespace sgam
{
	class TextComponent;
}

namespace digdug
{
	class LivesComponent final : public sgam::FunctionalComponent, public sgam::Observer
	{
	public:
		virtual void Update() override;

		virtual void OnNotify(const sgam::Event& event) override;

		void SetLives(const int lives) { m_Lives = lives; m_HasChanged = true; }

		explicit LivesComponent(sgam::GameObject* pOwner) : sgam::FunctionalComponent(pOwner) {}
		~LivesComponent() = default;
		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) = delete;

	private:
		void UpdateLives();

		sgam::TextComponent* m_pTextComponent{};

		int m_Lives{};

		bool m_HasChanged{ true };
	};
}
