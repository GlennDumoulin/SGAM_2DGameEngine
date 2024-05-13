#pragma once
#include <memory>

namespace digdug
{
	class State
	{
	public:
		virtual ~State() = default;

		virtual std::unique_ptr<State> Update() = 0;

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;
	};
}
