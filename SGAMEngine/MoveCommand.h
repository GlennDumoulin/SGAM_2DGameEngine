#pragma once
#include <glm/glm.hpp>

#include "GameObjectCommand.h"
#include "GameObject.h"
#include "MoveComponent.h"

namespace sgam
{
	class MoveCommand final : public GameObjectCommand
	{
	public:
		virtual void Execute() override;

		explicit MoveCommand(GameObject* pGameObject, const glm::vec2& direction);

	private:
		MoveComponent* m_pMoveComp{};

		glm::vec2 m_Direction{};
	};
}
