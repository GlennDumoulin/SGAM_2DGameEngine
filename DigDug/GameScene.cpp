#include <SDL.h>
#include <format>

#include "GameScene.h"

#include "ResourceManager.h"
#include "InputManager.h"
#include "GameManager.h"

#include "GameObject.h"
#include "Transform.h"
#include "GridComponent.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"

#include "FunctionCommand.h"

#include "LevelFileLoader.h"

void digdug::GameScene::Load(sgam::Scene* pScene)
{
	// Cache Singleton instances
	const auto& resourceManager = sgam::ResourceManager::GetInstance();
	auto& inputManager = sgam::InputManager::GetInstance();
	auto& gameManager = digdug::GameManager::GetInstance();

	// Grid GameObject
	auto pGrid = pScene->CreateGameObject();
	pGrid->GetTransform()->SetWorldPosition(0, 100);
	auto pGridComp = pGrid->AddComponent<digdug::GridComponent>();
	pGridComp->Init(12, 40);

	digdug::LevelFileLoader::Load(std::format("Levels/Level{}.json", gameManager.GetCurrentLevel()), pGridComp);

	// FPS GameObject
	auto pFPS = pScene->CreateGameObject();
	pFPS->SetEnabled(false);
	pFPS->GetTransform()->SetLocalPosition(10, 10);
	pFPS->AddComponent<sgam::TextureComponent>();
	auto pFPSTextComp = pFPS->AddComponent<sgam::TextComponent>();
	const auto& pMediumFont = resourceManager.LoadFont("Fonts/Lingua.otf", 18);
	pFPSTextComp->SetFont(pMediumFont);
	pFPS->AddComponent<sgam::FPSComponent>();

	// Toggle FPS Command
	pFPS->AddCommand(inputManager.BindKeyboardCommand(
		SDL_SCANCODE_F2, sgam::InputManager::InputType::ButtonDown,
		std::make_unique<sgam::FunctionCommand>(std::bind(&sgam::GameObject::ToggleEnabled, pFPS))
	));
}
