#pragma once
#include "State.h"

namespace sgam
{
	class GameObject;
}

namespace digdug
{
	class PookaGhostState final : public State
	{
	public:
		explicit PookaGhostState(sgam::GameObject* pOwner);
		~PookaGhostState() = default;
		PookaGhostState(const PookaGhostState& other) = delete;
		PookaGhostState(PookaGhostState&& other) = delete;
		PookaGhostState& operator=(const PookaGhostState& other) = delete;
		PookaGhostState& operator=(PookaGhostState&& other) = delete;

		virtual std::unique_ptr<State> Update() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		sgam::GameObject* m_pOwner{};

		float m_GhostTime{};

		const int m_MinGhostTime{ 2 };
		const int m_MaxGhostTime{ 5 };
	};
}