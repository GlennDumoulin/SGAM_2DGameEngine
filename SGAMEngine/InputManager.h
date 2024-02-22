#pragma once
#include "Singleton.h"

namespace sgam
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	};

}
