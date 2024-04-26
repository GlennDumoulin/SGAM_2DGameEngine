#pragma once
#include "Event.h"

namespace sgam
{
	class GameObject;
}

namespace digdug
{
	struct EntityDieEvent final : public sgam::Event
	{
	public:
		explicit EntityDieEvent(const sgam::GameObject* pEntity)
			: pEntity{ pEntity }
		{
		}

		const sgam::GameObject* pEntity;
	};

	struct ScoreChangedEvent final : public sgam::Event
	{
	public:
		explicit ScoreChangedEvent(const unsigned int score)
			: score{ score }
		{
		}

		const unsigned int score;
	};
}
