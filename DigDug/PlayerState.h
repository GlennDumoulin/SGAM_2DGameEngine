#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace digdug
{
	class PlayerState
	{
	public:
		virtual ~PlayerState() = default;

		virtual std::unique_ptr<PlayerState> HandleInput(const glm::vec2& movement, bool isPumping) = 0;
		virtual std::unique_ptr<PlayerState> Update() = 0;

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;
	};
}
