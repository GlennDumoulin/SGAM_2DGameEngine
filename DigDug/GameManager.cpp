#include <iostream>

#include "GameManager.h"
#include "SceneManager.h"
#include "InputManager.h"

using namespace digdug;

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

	//TEMP --> commands should be bound/unbound by components that need them
	sgam::InputManager::GetInstance().UnbindAll();
}
