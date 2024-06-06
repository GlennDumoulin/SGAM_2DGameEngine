#include <iostream>

#include "GridComponent.h"

using namespace digdug;

void GridComponent::Init(int gridSize, int tileSize)
{
	if (gridSize <= 0 || tileSize <= 0)
	{
		std::cout << "Can't initialize grid with negative grid or tile size!\n";
		return;
	}

	m_GridSize = gridSize;
	m_TileSize = tileSize;
}
