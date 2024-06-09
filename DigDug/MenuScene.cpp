#include "MenuScene.h"

#include "ResourceManager.h"
#include "InputManager.h"
#include "GameManager.h"
#include "SceneManager.h"

#include "GameObject.h"
#include "Texture2D.h"
#include "Transform.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"

#include "FunctionCommand.h"

void digdug::MenuScene::Load(sgam::Scene* pScene)
{
	// Cache Singleton instances
	const auto& resourceManager = sgam::ResourceManager::GetInstance();
	auto& inputManager = sgam::InputManager::GetInstance();
	auto& gameManager = digdug::GameManager::GetInstance();
	auto& sceneManager = sgam::SceneManager::GetInstance();

	constexpr int halfWidth{ 480 / 2 };
	constexpr int halfHeight{ 580 / 2 };
	const float menuScale{ 2.0f };

	// Logo GameObject
	auto pLogo = pScene->CreateGameObject();
	auto pLogoTextureComp = pLogo->AddComponent<sgam::TextureComponent>();
	const auto& pLogoTexture = resourceManager.LoadTexture("Menu/Logo.png");
	pLogo->GetTransform()->SetLocalScale(menuScale);
	const float logoXPos{ static_cast<float>(halfWidth - ((pLogoTexture->GetSize().x * menuScale) / 2)) };
	pLogo->GetTransform()->SetWorldPosition(
		logoXPos,
		100
	);
	pLogoTextureComp->SetTexture(pLogoTexture);

	// Singleplayer GameObject
	auto pSingleplayer = pScene->CreateGameObject();
	auto pSingleplayerTextureComp = pSingleplayer->AddComponent<sgam::TextureComponent>();
	const auto& pSingleplayerTexture = resourceManager.LoadTexture("Menu/Singleplayer.png");
	pSingleplayer->GetTransform()->SetLocalScale(menuScale);
	pSingleplayer->GetTransform()->SetWorldPosition(
		static_cast<float>(halfWidth - ((pSingleplayerTexture->GetSize().x * menuScale) / 2)),
		halfHeight - 75
	);
	pSingleplayerTextureComp->SetTexture(pSingleplayerTexture);

	// Singleplayer Command
	std::function<void()> singleplayerFunc{
		[&]() {
			gameManager.Reset(1);
			sceneManager.SetNextScene("GameScene");
		}
	};

	pSingleplayer->AddCommand(inputManager.BindKeyboardCommand(
		SDL_SCANCODE_1, sgam::InputManager::InputType::ButtonDown,
		std::make_unique<sgam::FunctionCommand>(singleplayerFunc)
	));
	pSingleplayer->AddCommand(inputManager.BindControllerCommand(
		0, sgam::InputManager::ControllerButton::A, sgam::InputManager::InputType::ButtonDown,
		std::make_unique<sgam::FunctionCommand>(singleplayerFunc)
	));

	// SingleplayerText GameObjects
	auto pSingleplayerText = pScene->CreateGameObject();
	pSingleplayerText->GetTransform()->SetWorldPosition(
		25,
		halfHeight - 35
	);
	pSingleplayerText->AddComponent<sgam::TextureComponent>();
	auto pSingleplayerTextComp = pSingleplayerText->AddComponent<sgam::TextComponent>();
	const auto& pGamemodeFont = resourceManager.LoadFont("Fonts/Arcade.ttf", 12);
	pSingleplayerTextComp->SetFont(pGamemodeFont);
	pSingleplayerTextComp->SetText("Press A (controller) or 1 (keyboard)");

	// Multiplayer GameObject
	auto pMultiplayer = pScene->CreateGameObject();
	auto pMultiplayerTextureComp = pMultiplayer->AddComponent<sgam::TextureComponent>();
	const auto& pMultiplayerTexture = resourceManager.LoadTexture("Menu/Multiplayer.png");
	pMultiplayer->GetTransform()->SetLocalScale(menuScale);
	pMultiplayer->GetTransform()->SetWorldPosition(
		static_cast<float>(halfWidth - ((pMultiplayerTexture->GetSize().x * menuScale) / 2)),
		halfHeight + 50
	);
	pMultiplayerTextureComp->SetTexture(pMultiplayerTexture);

	// Multiplayer Command
	std::function<void()> multiplayerFunc{
		[&]() {
			gameManager.Reset(2);
			sceneManager.SetNextScene("GameScene");
		}
	};

	pMultiplayer->AddCommand(inputManager.BindKeyboardCommand(
		SDL_SCANCODE_2, sgam::InputManager::InputType::ButtonDown,
		std::make_unique<sgam::FunctionCommand>(multiplayerFunc)
	));
	pMultiplayer->AddCommand(inputManager.BindControllerCommand(
		0, sgam::InputManager::ControllerButton::B, sgam::InputManager::InputType::ButtonDown,
		std::make_unique<sgam::FunctionCommand>(multiplayerFunc)
	));

	// MultiplayerText GameObjects
	auto pMultiplayerText = pScene->CreateGameObject();
	pMultiplayerText->GetTransform()->SetWorldPosition(
		25,
		halfHeight + 90
	);
	pMultiplayerText->AddComponent<sgam::TextureComponent>();
	auto pMultiplayerTextComp = pMultiplayerText->AddComponent<sgam::TextComponent>();
	pMultiplayerTextComp->SetFont(pGamemodeFont);
	pMultiplayerTextComp->SetText("Press B (controller) or 2 (keyboard)");

	// Rights GameObject
	auto pRights = pScene->CreateGameObject();
	auto pRightsTextureComp = pRights->AddComponent<sgam::TextureComponent>();
	const auto& pRightsTexture = resourceManager.LoadTexture("Menu/Rights.png");
	pRights->GetTransform()->SetLocalScale(menuScale);
	pRights->GetTransform()->SetWorldPosition(
		static_cast<float>(halfWidth - ((pRightsTexture->GetSize().x * menuScale) / 2)),
		1.6 * halfHeight
	);
	pRightsTextureComp->SetTexture(pRightsTexture);

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
