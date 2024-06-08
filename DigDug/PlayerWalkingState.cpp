#include <format>
#include <algorithm>
#include <iostream>

#include "PlayerWalkingState.h"

#include "ResourceManager.h"
#include "InputManager.h"
#include "SGAMTime.h"

#include "GameObject.h"
#include "Transform.h"
#include "PlayerComponent.h"
#include "TextureComponent.h"
#include "GridComponent.h"

#include "GridMoveCommand.h"

using namespace digdug;

PlayerWalkingState::PlayerWalkingState(PlayerComponent* pPlayer)
	: m_pPlayer{ pPlayer }
{
	m_pGrid = m_pPlayer->GetParent()->GetComponent<GridComponent>();
	if (!m_pGrid)
	{
		std::cout << "Couldn't find GridComponent on Player's parent object! Player won't snap to grid!\n";
	}
}

std::unique_ptr<PlayerState> PlayerWalkingState::HandleInput(const glm::vec2& movement, bool isPumping)
{
	// If we are pumping, go to pumping State
	if (isPumping) return nullptr;

	// Add the movement input
	m_MovementInput += movement;

	// Clamp the movement input [-1, 1]
	m_MovementInput.x = std::clamp(m_MovementInput.x, -1.0f, 1.0f);
	m_MovementInput.y = std::clamp(m_MovementInput.y, -1.0f, 1.0f);

	return nullptr;
}

std::unique_ptr<PlayerState> PlayerWalkingState::Update()
{
	// Check if there is any movement to be handled
	if (m_MovementInput == glm::vec2{ 0.0f, 0.0f }) return nullptr;

	// Handle walking
	const glm::vec2 snappedPos{ ValidateMoveDirection() };

	// Check if there is any movement to be handled
	if (m_MovementInput == glm::vec2{ 0.0f, 0.0f }) return nullptr;

	const glm::vec2 translation{ m_MovementInput * sgam::Time::GetInstance().Delta() * m_MoveSpeed };
	m_pPlayer->GetTransform()->SetLocalPosition(snappedPos + translation);

	// Update prev movement
	m_PrevMovement = m_MovementInput;

	// Reset movement input
	m_MovementInput = glm::vec2{ 0.0f, 0.0f };

	return nullptr;
}

const glm::vec2 PlayerWalkingState::ValidateMoveDirection()
{
	// Cache player pos
	const glm::vec2 currentPos{ m_pPlayer->GetTransform()->GetLocalPosition() };

	// Check if we have a GridComponent
	if (!m_pGrid) return currentPos;

	// Cache grid data
	const int gridSize{ m_pGrid->GetGridSize() };
	const int tileSize{ m_pGrid->GetTileSize() };

	glm::vec2 snappedPos{ SnapToGrid(tileSize, currentPos) };
	ClampToGridBorders(gridSize, tileSize, snappedPos);

	return snappedPos;
}

glm::vec2 PlayerWalkingState::SnapToGrid(int tileSize, const glm::vec2& currentPos)
{
	glm::vec2 snappedPos{ currentPos };

	// Get remainder from being aligned with { column, row }
	const glm::ivec2 remainder{
		ClosestAlignment(static_cast<int>(currentPos.x), tileSize),
		ClosestAlignment(static_cast<int>(currentPos.y), tileSize)
	};

	// Prioritize horizontal over vertical movement
	if (m_MovementInput.x != 0.0f)
	{
		// Check if player is aligned with row
		if (abs(remainder.y) <= m_RemainderEpsilon)
		{
			// If so, cancel vertical movement
			m_MovementInput.y = 0.0f;

			// Make sure we are exactly aligned
			snappedPos.y -= remainder.y;
		}
		else
		{
			// If not, cancel horizontal movement and continue previous movement
			m_MovementInput.x = 0.0f;
			m_MovementInput.y = m_PrevMovement.y;
		}
		
		return snappedPos;
	}

	// Check if player is aligned with column
	if (abs(remainder.x) <= m_RemainderEpsilon)
	{
		// If so, cancel horizontal movement
		m_MovementInput.x = 0.0f;

		// Make sure we are exactly aligned
		snappedPos.x -= remainder.x;
	}
	else
	{
		// If not, cancel vertical movement and continue previous movement
		m_MovementInput.x = m_PrevMovement.x;
		m_MovementInput.y = 0.0f;
	}

	return snappedPos;
}

int PlayerWalkingState::ClosestAlignment(int a, int b) const
{
	/* https://godbolt.org/z/MY5j6qarz */
	int remainder{ a % b };
	if (remainder > b / 2) remainder = -b + remainder;
	else if (remainder < -b / 2) remainder = b + remainder;

	return remainder;
}

void PlayerWalkingState::ClampToGridBorders(int gridSize, int tileSize, glm::vec2& currentPos)
{
	// Clamp player between grid borders
	const glm::vec2 gridMin{ 0.0f, static_cast<float>(-tileSize) };
	const float gridMax{ static_cast<float>(tileSize * (gridSize - 1)) };

	if (currentPos.x <= gridMin.x && m_MovementInput.x == -1.0f)
	{
		m_MovementInput.x = 0.0f;
		currentPos.x = gridMin.x;
	}
	else if (currentPos.x >= gridMax && m_MovementInput.x == 1.0f)
	{
		m_MovementInput.x = 0.0f;
		currentPos.x = gridMax;
	}

	if (currentPos.y <= gridMin.y && m_MovementInput.y == -1.0f)
	{
		m_MovementInput.y = 0.0f;
		currentPos.y = gridMin.y;
	}
	else if (currentPos.y >= gridMax && m_MovementInput.y == 1.0f)
	{
		m_MovementInput.y = 0.0f;
		currentPos.y = gridMax;
	}
}

void PlayerWalkingState::OnEnter()
{
	const int playerIdx{ m_pPlayer->GetPlayerIdx() };
	sgam::GameObject* pOwner{ m_pPlayer->GetOwner() };

	// Set the walking texture
	std::string texturePath{ std::format("DigDug{}/Walking.png", playerIdx) };
	const auto& pTexture{ sgam::ResourceManager::GetInstance().LoadTexture(texturePath) };
	pOwner->GetComponent<sgam::TextureComponent>()->SetTexture(pTexture);

	// Bind commands
	if (playerIdx == 0) BindKeyboardCommands();
	BindControllerCommands();
}

void PlayerWalkingState::BindKeyboardCommands()
{
	auto& inputManager = sgam::InputManager::GetInstance();

	// Move Commands
	inputManager.BindKeyboardCommand(
		SDL_SCANCODE_W, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<GridMoveCommand>(m_pPlayer, glm::vec2{ 0.f, -1.f })
	);
	inputManager.BindKeyboardCommand(
		SDL_SCANCODE_D, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<GridMoveCommand>(m_pPlayer, glm::vec2{ 1.f, 0.f })
	);
	inputManager.BindKeyboardCommand(
		SDL_SCANCODE_S, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<GridMoveCommand>(m_pPlayer, glm::vec2{ 0.f, 1.f })
	);
	inputManager.BindKeyboardCommand(
		SDL_SCANCODE_A, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<GridMoveCommand>(m_pPlayer, glm::vec2{ -1.f, 0.f })
	);
}

void PlayerWalkingState::BindControllerCommands()
{
	auto& inputManager = sgam::InputManager::GetInstance();
	const int controllerIdx{ m_pPlayer->GetControllerIdx() };

	// Move Commands
	inputManager.BindControllerCommand(
		controllerIdx, sgam::InputManager::ControllerButton::DPAD_UP, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<GridMoveCommand>(m_pPlayer, glm::vec2{ 0.f, -1.f })
	);
	inputManager.BindControllerCommand(
		controllerIdx, sgam::InputManager::ControllerButton::DPAD_RIGHT, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<GridMoveCommand>(m_pPlayer, glm::vec2{ 1.f, 0.f })
	);
	inputManager.BindControllerCommand(
		controllerIdx, sgam::InputManager::ControllerButton::DPAD_DOWN, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<GridMoveCommand>(m_pPlayer, glm::vec2{ 0.f, 1.f })
	);
	inputManager.BindControllerCommand(
		controllerIdx, sgam::InputManager::ControllerButton::DPAD_LEFT, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<GridMoveCommand>(m_pPlayer, glm::vec2{ -1.f, 0.f })
	);
}

void PlayerWalkingState::OnExit()
{
	// Unbind commands
	for (auto pCommand : m_pCommands)
	{
		sgam::InputManager::GetInstance().UnbindCommand(pCommand);
	}
}
