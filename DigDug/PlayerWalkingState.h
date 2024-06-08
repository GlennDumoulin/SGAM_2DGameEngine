#pragma once
#include <vector>

#include "PlayerState.h"
#include "Command.h"

namespace digdug
{
	class PlayerComponent;
	class GridComponent;

	class PlayerWalkingState final : public PlayerState
	{
	public:
		explicit PlayerWalkingState(PlayerComponent* pPlayer);
		~PlayerWalkingState() = default;
		PlayerWalkingState(const PlayerWalkingState& other) = delete;
		PlayerWalkingState(PlayerWalkingState&& other) = delete;
		PlayerWalkingState& operator=(const PlayerWalkingState& other) = delete;
		PlayerWalkingState& operator=(PlayerWalkingState&& other) = delete;

		virtual std::unique_ptr<PlayerState> HandleInput(const glm::vec2& movement, bool isPumping) override;
		virtual std::unique_ptr<PlayerState> Update() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		const glm::vec2 ValidateMoveDirection();
		glm::vec2 SnapToGrid(int tileSize, const glm::vec2& currentPos);
		int ClosestAlignment(int a, int b) const;
		void ClampToGridBorders(int gridSize, int tileSize, glm::vec2& currentPos);

		void BindKeyboardCommands();
		void BindControllerCommands();

		PlayerComponent* m_pPlayer{};
		GridComponent* m_pGrid{};

		const float m_MoveSpeed{ 80.0f };
		const int m_RemainderEpsilon{ 2 };

		glm::vec2 m_PrevMovement{ 0.0f, 0.0f };
		glm::vec2 m_MovementInput{ 0.0f, 0.0f };

		std::vector<sgam::Command*> m_pCommands{};
	};
}
