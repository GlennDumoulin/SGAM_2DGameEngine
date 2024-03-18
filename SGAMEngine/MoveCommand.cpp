#include "MoveCommand.h"

using namespace sgam;

MoveCommand::MoveCommand(GameObject* pGameObject, const glm::vec2& direction)
	: GameObjectCommand(pGameObject)
	, m_Direction{ direction }
{
}

void MoveCommand::Execute()
{
	// Check if the GameObject has a MoveComponent
	if (!m_pMoveComp)
	{
		m_pMoveComp = GetGameObject()->GetComponent<MoveComponent>();

		if (!m_pMoveComp)
		{
			std::cout << "MoveCommand can't execute without MoveComponent\n";
			return;
		}
	}

	// Add move direction
	m_pMoveComp->AddMovement(m_Direction);
}
