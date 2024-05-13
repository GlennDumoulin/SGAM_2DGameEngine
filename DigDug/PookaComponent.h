#pragma once
#include "FunctionalComponent.h"
#include "State.h"

namespace digdug
{
	class PookaComponent final : public sgam::FunctionalComponent
	{
	public:
		explicit PookaComponent(sgam::GameObject* pOwner);
		~PookaComponent() = default;
		PookaComponent(const PookaComponent& other) = delete;
		PookaComponent(PookaComponent&& other) = delete;
		PookaComponent& operator=(const PookaComponent& other) = delete;
		PookaComponent& operator=(PookaComponent&& other) = delete;

		virtual void Update() override;

	private:
		void SetState(std::unique_ptr<State> newState);

		std::unique_ptr<State> m_State{};
	};
}
