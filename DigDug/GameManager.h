#pragma once
#include "Singleton.h"
#include "Command.h"

namespace digdug
{
	class GameManager final : public sgam::Singleton<GameManager>
	{
	public:
		void LevelCompleted();

		const int GetCurrentLevel() const { return m_CurrentLevel; }

		const int GetNrOfPlayers() const { return m_NrOfPlayers; }
		void SetNrOfPlayers(int nrOfPlayers);

	private:
		friend class Singleton<GameManager>;
		explicit GameManager();
		~GameManager();
		GameManager(const GameManager& other) = delete;
		GameManager(GameManager&& other) = delete;
		GameManager& operator=(const GameManager& other) = delete;
		GameManager& operator=(GameManager&& other) = delete;

		const int m_NrOfLevels{ 3 };
		int m_CurrentLevel{ 1 };

		int m_NrOfPlayers{ 1 };

		sgam::Command* m_pSkipLevelCommand{};
	};
}
