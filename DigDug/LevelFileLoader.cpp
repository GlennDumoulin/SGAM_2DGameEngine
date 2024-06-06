#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>

#include "LevelFileLoader.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "TextureComponent.h"

void digdug::LevelFileLoader::Load(const std::string& filename, GridComponent* pGrid)
{
	// Check filename & pGrid
	if (filename.empty() || !pGrid)
	{
		std::cout << "Failed to load level file! Invalid filename or GameObject!\n";
		return;
	}

	auto pGridObject{ pGrid->GetOwner() };

	const auto& resourceManager{ sgam::ResourceManager::GetInstance() };

	// Get the json data from the file, then close it
	std::ifstream file{ resourceManager.LoadFile(filename) };
	nlohmann::json json{ nlohmann::json::parse(file) };
	file.close();

	// Load json data into LevelInfo
	LevelInfo info{ json.get<LevelInfo>() };

	// Cache the layer textures
	std::vector<std::shared_ptr<sgam::Texture2D>> layerTextures{};
	for (const std::string& layerTexture : info.layerTextures)
	{
		layerTextures.push_back(resourceManager.LoadTexture(layerTexture));
	}
	if (layerTextures.size() != 4)
	{
		std::cout << "Failed to load level file! Level loading requires 4 layer textures!\n";
		return;
	}

	// Get grid sizes
	const int gridSize{ pGrid->GetGridSize() };
	const int tileSize{ pGrid->GetTileSize() };

	// Create the grid tiles
	glm::ivec2 gridTileIdx{};

	for (int x{}; x < gridSize; ++x)
	{
		gridTileIdx.x = x;

		for (int y{}; y < gridSize; ++y)
		{
			gridTileIdx.y = y;

			// Check if there is a tunnel on the current grid tile
			if (std::find(info.tunnels.begin(), info.tunnels.end(), gridTileIdx) != info.tunnels.end())
				continue;

			// Create the grid tile
			const glm::vec2 tilePos{
				x * tileSize,
				y * tileSize
			};
			const int layerIdx{ y / 3 };
			CreateGridTile(pGridObject, tilePos, layerTextures.at(layerIdx), tileSize);
		}
	}
}

void digdug::LevelFileLoader::CreateGridTile(sgam::GameObject* pObject, const glm::vec2& tilePos, std::shared_ptr<sgam::Texture2D> pTexture, int dstSize)
{
	// Create tile GameObject
	auto pTile{ pObject->CreateGameObject() };

	// Set tile Position
	pTile->GetTransform()->SetLocalPosition(tilePos);

	// Set tile Texture
	auto pTileTexture{ pTile->AddComponent<sgam::TextureComponent>() };
	pTileTexture->SetTexture(pTexture);
	pTileTexture->SetDstSize(dstSize, dstSize);
}
