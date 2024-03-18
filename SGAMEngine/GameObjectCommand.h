#pragma once
#include "Command.h"
#include "GameObject.h"

namespace sgam
{
	class GameObjectCommand : public Command
	{
	public:
		GameObjectCommand(GameObject* pGameObject) : m_pGO{ pGameObject } {}
		virtual ~GameObjectCommand() = default;

	protected:
		GameObject* GetGameObject() const { return m_pGO; }

	private:
		GameObject* m_pGO{};
	};
}
