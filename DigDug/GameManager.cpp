#include <iostream>
#include <stdexcept>

#include "GameManager.h"
#include "SceneManager.h"
#include "InputManager.h"

#include "FunctionCommand.h"

using namespace digdug;

GameManager::GameManager()
{
	auto& inputManager{ sgam::InputManager::GetInstance() };

	// Bind skip level Command
	m_pSkipLevelCommand = inputManager.BindKeyboardCommand(
		SDL_SCANCODE_F1, sgam::InputManager::InputType::ButtonDown,
		std::make_unique<sgam::FunctionCommand>(std::bind(&digdug::GameManager::LevelCompleted, this))
	);
}

GameManager::~GameManager()
{
	// Unbind skip level Command
	sgam::InputManager::GetInstance().UnbindCommand(m_pSkipLevelCommand);
}

void GameManager::LevelCompleted()
{
	// Check if we completed the last level
	if (m_CurrentLevel == m_NrOfLevels)
	{
		std::cout << "All levels completed!\n";
		return;
	}

	// If not, prepare the next level
	++m_CurrentLevel;
	sgam::SceneManager::GetInstance().ReloadScene();
}

void GameManager::SetNrOfPlayers(int nrOfPlayers)
{
	if (nrOfPlayers <= 0)
	{
		throw std::runtime_error("Can't set nrOfPlayers to 0 or less!");
	}

	m_NrOfPlayers = nrOfPlayers;
}
