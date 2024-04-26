#pragma once
#include "FunctionalComponent.h"
#include "Observer.h"
#include "Subject.h"

namespace sgam
{
	class TextComponent;
}

namespace digdug
{
	class ScoreComponent final : public sgam::FunctionalComponent, public sgam::Observer
	{
	public:
		virtual void Update() override;

		virtual void OnNotify(const sgam::Event& event) override;

		explicit ScoreComponent(sgam::GameObject* pOwner) : FunctionalComponent(pOwner) {}
		~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		std::unique_ptr<sgam::Subject> OnScoreChanged{ std::make_unique<sgam::Subject>() };

	private:
		void UpdateScore();

		sgam::TextComponent* m_pTextComponent{};

		unsigned int m_Score{};

		bool m_HasChanged{ true };
	};
}
