#pragma once
#include <glm/glm.hpp>

#include "Command.h"
#include "PlayerComponent.h"

namespace digdug
{
	class GridMoveCommand final : public sgam::Command
	{
	public:
		virtual void Execute() override;

		explicit GridMoveCommand(PlayerComponent* pPlayer, const glm::vec2& direction);
		~GridMoveCommand() = default;

	private:
		PlayerComponent* m_pPlayer{};

		glm::vec2 m_Direction{};
	};
}

