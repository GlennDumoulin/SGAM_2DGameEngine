#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <memory>
#include <algorithm>

#include "ResourceManager.h"
#include "GameManager.h"

#include "LevelFileLoader.h"
#include "Transform.h"
#include "TextureComponent.h"
#include "PlayerComponent.h"
#include "PookaComponent.h"
#include "FygarComponent.h"

using namespace digdug;

void LevelFileLoader::Load(const std::string& filename, GridComponent* pGrid)
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

	// Create the entities
	int currentPlayerIdx{ 0 };
	int nrOfEnemies{ 0 };
	for (const auto& entity : info.entities)
	{
		// Check if the entity's tile is a tunnel
		if (std::find(info.tunnels.begin(), info.tunnels.end(), entity.pos) == info.tunnels.end())
			continue;

		// Get the entity's position
		const glm::vec2 tilePos{
				entity.pos.x * tileSize,
				entity.pos.y * tileSize
		};

		switch (entity.type)
		{
		case EntityType::Player:
		{
			CreatePlayer(pGridObject, tilePos, tileSize, currentPlayerIdx);
			++currentPlayerIdx;
			break;
		}
		case EntityType::Pooka:
		{
			CreatePooka(pGridObject, tilePos, tileSize);
			++nrOfEnemies;
			break;
		}
		case EntityType::Fygar:
		{
			CreateFygar(pGridObject, tilePos, tileSize);
			++nrOfEnemies;
			break;
		}
		default:
			break;
		}
	}

	// Check if we have the correct amount of players
	if (currentPlayerIdx != GameManager::GetInstance().GetNrOfPlayers())
	{
		throw std::runtime_error("Invalid amount of player entities given!");
	}

	// Check if we have at least 1 enemy
	if (nrOfEnemies == 0)
	{
		throw std::runtime_error("Invalid amount of enemy entities given!");
	}
}

void LevelFileLoader::CreateGridTile(sgam::GameObject* pObject, const glm::vec2& tilePos, std::shared_ptr<sgam::Texture2D> pTexture, const int& dstSize)
{
	// Create tile GameObject
	auto pTile{ pObject->CreateGameObject() };

	// Set tile Position
	pTile->GetTransform()->SetLocalPosition(tilePos);

	// Set tile Scale
	const glm::vec2 texSize{ pTexture->GetSize() };
	const glm::vec2 tileScale{ static_cast<float>(dstSize) / texSize };
	pTile->GetTransform()->SetLocalScale(tileScale);

	// Set tile Texture
	auto pTileTexture{ pTile->AddComponent<sgam::TextureComponent>() };
	pTileTexture->SetTexture(pTexture);
}

void LevelFileLoader::CreatePlayer(sgam::GameObject* pObject, const glm::vec2& tilePos, const int& dstSize, const int& playerIdx)
{
	// Create player GameObject
	auto pPlayer{ pObject->CreateGameObject() };

	// Set player Position
	pPlayer->GetTransform()->SetLocalPosition(tilePos);

	// Get temporary player texture
	std::string texturePath{ std::format("DigDug{}/Walking.png", playerIdx)};
	const auto& pTexture{ sgam::ResourceManager::GetInstance().LoadTexture(texturePath) };

	// Set player Scale
	const glm::vec2 texSize{ pTexture->GetSize() };
	const glm::vec2 tileScale{ static_cast<float>(dstSize) / texSize };
	pPlayer->GetTransform()->SetLocalScale(tileScale);

	// Add player Components
	pPlayer->AddComponent<sgam::TextureComponent>();
	auto pPlayerComp{ pPlayer->AddComponent<digdug::PlayerComponent>() };
	pPlayerComp->Init(playerIdx);

	// Add player Collider
	auto pPlayerCollider = pPlayer->AddCollider();
	pPlayerCollider->OnCollisionEnter->AddObserver(pPlayerComp);
}

void LevelFileLoader::CreatePooka(sgam::GameObject* pObject, const glm::vec2& tilePos, const int& dstSize)
{
	// Create pooka GameObject
	auto pPooka{ pObject->CreateGameObject() };

	// Set pooka Position
	pPooka->GetTransform()->SetLocalPosition(tilePos);

	// Get temporary pooka texture
	std::string texturePath{ "Pooka/Default.png" };
	const auto& pTexture{ sgam::ResourceManager::GetInstance().LoadTexture(texturePath) };

	// Set pooka Scale
	const glm::vec2 texSize{ pTexture->GetSize() };
	const glm::vec2 tileScale{ static_cast<float>(dstSize) / texSize };
	pPooka->GetTransform()->SetLocalScale(tileScale);

	// Add pooka Components
	pPooka->AddComponent<sgam::TextureComponent>();
	pPooka->AddComponent<digdug::PookaComponent>();

	// Add pooka Collider
	pPooka->AddCollider();
}

void LevelFileLoader::CreateFygar(sgam::GameObject* pObject, const glm::vec2& tilePos, const int& dstSize)
{
	// Create fygar GameObject
	auto pFygar{ pObject->CreateGameObject() };

	// Set fygar Position
	pFygar->GetTransform()->SetLocalPosition(tilePos);

	// Get temporary fygar texture
	std::string texturePath{ "Fygar/Default.png" };
	const auto& pTexture{ sgam::ResourceManager::GetInstance().LoadTexture(texturePath) };

	// Set fygar Scale
	const glm::vec2 texSize{ pTexture->GetSize() };
	const glm::vec2 tileScale{ static_cast<float>(dstSize) / texSize };
	pFygar->GetTransform()->SetLocalScale(tileScale);

	// Add fygar Components
	pFygar->AddComponent<sgam::TextureComponent>();
	pFygar->AddComponent<digdug::FygarComponent>();

	// Add fygar Collider
	pFygar->AddCollider();
}

LevelFileLoader::EntityType LevelFileLoader::ConvertToEntityType(const std::string& type)
{
	if (type == "player") return EntityType::Player;
	if (type == "pooka") return EntityType::Pooka;
	if (type == "fygar") return EntityType::Fygar;

	return EntityType::Invalid;
}
