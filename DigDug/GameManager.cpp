#include <iostream>
#include <stdexcept>

#include "Events.h"

#include "GameManager.h"
#include "SceneManager.h"
#include "InputManager.h"

#include "PlayerComponent.h"

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

void GameManager::SetPlayer(PlayerComponent* pPlayer)
{
	// Check if there is a player
	if (!pPlayer) return;

	const int playerIdx{ pPlayer->GetPlayerIdx() };
	if (m_pPlayers.size() <= static_cast<size_t>(playerIdx))
	{
		const size_t newSize{ static_cast<size_t>(playerIdx + 1) };
		m_pPlayers.resize(newSize);
		m_PlayersHealth.resize(newSize);

		// Add the player's health
		m_PlayersHealth.at(playerIdx) = pPlayer->GetHealth();
	}
	else
	{
		// If the player already existed set it's previous health
		pPlayer->SetHealth(GetPlayerHealth(playerIdx));
	}

	// Add the player
	m_pPlayers.at(playerIdx) = pPlayer;

	// Add ourself to listen to player died events
	pPlayer->OnPlayerDied->AddObserver(this);
}

int GameManager::GetPlayerHealth(int playerIdx) const
{
	if (static_cast<size_t>(playerIdx) >= m_PlayersHealth.size()) return -1;

	return m_PlayersHealth.at(playerIdx);
}

void GameManager::OnNotify(const sgam::Event& event)
{
	// Check if we were notified by an EntityDieEvent
	if (auto entityDieEvent{ dynamic_cast<const EntityDieEvent*>(&event) })
	{
		// Check if the event is valid (contains an entity)
		if (entityDieEvent->pEntity)
		{
			// Check if the entity is a player
			PlayerComponent* pPlayer{ entityDieEvent->pEntity->GetComponent<PlayerComponent>() };
			if (!pPlayer) return;

			// Find the player
			const int nrOfPlayers{ static_cast<int>(m_pPlayers.size()) };
			for (int i{}; i < nrOfPlayers; ++i)
			{
				if (m_pPlayers.at(i) == pPlayer)
				{
					// Save it's updated health
					m_PlayersHealth.at(i) = pPlayer->GetHealth();

					// Reload the scene
					sgam::SceneManager::GetInstance().ReloadScene();
					return;
				}
			}
		}
	}
}
