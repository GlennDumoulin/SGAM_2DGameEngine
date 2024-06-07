#pragma once
#include "Singleton.h"

namespace digdug
{
	class GameManager final : public sgam::Singleton<GameManager>
	{
	public:
		void LevelCompleted();

		const int GetCurrentLevel() const { return m_CurrentLevel; }

	private:
		friend class Singleton<GameManager>;
		explicit GameManager() = default;
		~GameManager() = default;
		GameManager(const GameManager& other) = delete;
		GameManager(GameManager&& other) = delete;
		GameManager& operator=(const GameManager& other) = delete;
		GameManager& operator=(GameManager&& other) = delete;

		const int m_NrOfLevels{ 3 };
		int m_CurrentLevel{ 1 };
	};
}
