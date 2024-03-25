#pragma once
#include "FunctionalComponent.h"
#include "Observer.h"

namespace sgam
{
	class TextComponent;

	class LivesComponent final : public FunctionalComponent, public Observer
	{
	public:
		virtual void Update() override;

		virtual void OnNotify(const Event& event) override;

		void SetLives(const int lives) { m_Lives = lives; m_HasChanged = true; }

		explicit LivesComponent(GameObject* pOwner) : FunctionalComponent(pOwner) {}
		~LivesComponent() = default;
		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) = delete;

	private:
		void UpdateLives();

		TextComponent* m_pTextComponent{};

		int m_Lives{};

		bool m_HasChanged{ true };
	};
}
