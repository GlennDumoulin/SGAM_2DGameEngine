#pragma once
#include <functional>

#include "Command.h"

namespace sgam
{
	class FunctionCommand final : public Command
	{
	public:
		explicit FunctionCommand(std::function<void()> func) : m_Function{ func } {}
		~FunctionCommand() = default;

		virtual void Execute() override
		{
			m_Function();
		}

	private:
		std::function<void()> m_Function{};
	};
}
