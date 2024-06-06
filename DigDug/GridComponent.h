#pragma once
#include "FunctionalComponent.h"

namespace digdug
{
	class GridComponent final : public sgam::FunctionalComponent
	{
	public:
		void Init(int gridSize, int tileSize);

		const int GetGridSize() const { return m_GridSize; }
		const int GetTileSize() const { return m_TileSize; }

		explicit GridComponent(sgam::GameObject* pOwner) : sgam::FunctionalComponent(pOwner) {}
		~GridComponent() = default;
		GridComponent(const GridComponent& other) = delete;
		GridComponent(GridComponent&& other) = delete;
		GridComponent& operator=(const GridComponent& other) = delete;
		GridComponent& operator=(GridComponent&& other) = delete;

	private:
		int m_GridSize{};
		int m_TileSize{};
	};
}
