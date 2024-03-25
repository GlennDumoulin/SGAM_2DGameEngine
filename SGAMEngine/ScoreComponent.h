#pragma once
#include "FunctionalComponent.h"
#include "Observer.h"
#include "Subject.h"

namespace sgam
{
	class TextComponent;

	class ScoreComponent final : public FunctionalComponent, public Observer
	{
	public:
		virtual void Update() override;

		virtual void OnNotify(const Event& event) override;

		explicit ScoreComponent(GameObject* pOwner) : FunctionalComponent(pOwner) {}
		~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		std::unique_ptr<Subject> OnScoreChanged{ std::make_unique<Subject>() };

	private:
		void UpdateScore();

		TextComponent* m_pTextComponent{};

		unsigned int m_Score{};

		bool m_HasChanged{ true };
	};
}
