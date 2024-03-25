#pragma once
#include "Event.h"

namespace sgam
{
	class GameObject;

	struct EntityDieEvent final : public Event
	{
	public:
		explicit EntityDieEvent(const GameObject* pEntity)
			: pEntity{ pEntity }
		{
		}

		const GameObject* pEntity;
	};
}
