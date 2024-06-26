#pragma once
#include <vector>

#include "Singleton.h"
#include "Command.h"
#include "Observer.h"

#include "PlayerComponent.h"

namespace digdug
{
	class GameManager final : public sgam::Singleton<GameManager>, public sgam::Observer
	{
	public:
		void Reset(int nrOfPlayers);

		void LevelCompleted();

		const int GetCurrentLevel() const { return m_CurrentLevel; }

		const int GetNrOfPlayers() const { return m_NrOfPlayers; }

		void SetPlayer(PlayerComponent* pPlayer);
		int GetPlayerHealth(int playerIdx) const;

		virtual void OnNotify(const sgam::Event& event) override;

	private:
		friend class Singleton<GameManager>;
		explicit GameManager();
		~GameManager();
		GameManager(const GameManager& other) = delete;
		GameManager(GameManager&& other) = delete;
		GameManager& operator=(const GameManager& other) = delete;
		GameManager& operator=(GameManager&& other) = delete;

		void SetNrOfPlayers(int nrOfPlayers);

		const int m_NrOfLevels{ 3 };
		int m_CurrentLevel{ 1 };

		int m_NrOfPlayers{ 1 };
		std::vector<PlayerComponent*> m_pPlayers{};
		std::vector<int> m_PlayersHealth{};

		sgam::Command* m_pSkipLevelCommand{};
		std::vector<sgam::Command*> m_pGoToMenuCommands{};
	};
}
