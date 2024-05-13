#pragma once
#include "State.h"

namespace sgam
{
	class GameObject;
}

namespace digdug
{
	class PookaWanderState final : public State
	{
	public:
		explicit PookaWanderState(sgam::GameObject* pOwner);
		~PookaWanderState() = default;
		PookaWanderState(const PookaWanderState& other) = delete;
		PookaWanderState(PookaWanderState&& other) = delete;
		PookaWanderState& operator=(const PookaWanderState& other) = delete;
		PookaWanderState& operator=(PookaWanderState&& other) = delete;

		virtual std::unique_ptr<State> Update() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		sgam::GameObject* m_pOwner{};

		float m_WanderTime{};

		const int m_MinWanderTime{ 5 };
		const int m_MaxWanderTime{ 10 };
	};
}
