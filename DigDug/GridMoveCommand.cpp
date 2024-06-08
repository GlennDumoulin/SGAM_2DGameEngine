#include "GridMoveCommand.h"

using namespace digdug;

GridMoveCommand::GridMoveCommand(PlayerComponent* pPlayer, const glm::vec2& direction)
	: m_pPlayer{ pPlayer }
	, m_Direction{ direction }
{
}

void GridMoveCommand::Execute()
{
	// Add move direction
	m_pPlayer->AddMovement(m_Direction);
}
