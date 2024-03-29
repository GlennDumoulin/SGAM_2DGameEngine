#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Engine.h"
#include "Scene.h"
#include "GameObject.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "InputManager.h"

#include "Transform.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "MoveComponent.h"
#include "PlayerComponent.h"
#include "ScoreComponent.h"
#include "LivesComponent.h"
#include "AchievementUnlocker.h"

#include "MoveCommand.h"
#include "FunctionCommand.h"

void load()
{
	auto& pScene = sgam::SceneManager::GetInstance().CreateScene("Demo");
	const auto& resourceManager = sgam::ResourceManager::GetInstance();
	auto& inputManager = sgam::InputManager::GetInstance();

	// Background GameObject
	auto pBackground = pScene.CreateGameObject();
	auto pBackgroundTextureComp = pBackground->AddComponent<sgam::TextureComponent>();
	const auto& pBackgroundTexture = resourceManager.LoadTexture("background.tga");
	pBackgroundTextureComp->SetTexture(pBackgroundTexture);

	// Logo GameObject
	auto pLogo = pScene.CreateGameObject();
	pLogo->GetTransform()->SetLocalPosition(216, 180);
	auto pLogoTextureComp = pLogo->AddComponent<sgam::TextureComponent>();
	const auto& pLogoTexture = resourceManager.LoadTexture("logo.tga");
	pLogoTextureComp->SetTexture(pLogoTexture);

	// Text GameObject
	auto pText = pScene.CreateGameObject();
	pText->GetTransform()->SetLocalPosition(80, 20);
	pText->AddComponent<sgam::TextureComponent>();
	auto pTextComp = pText->AddComponent<sgam::TextComponent>();
	const auto& pLargeFont = resourceManager.LoadFont("Lingua.otf", 36);
	pTextComp->SetFont(pLargeFont);
	pTextComp->SetText("Programming 4 Assignment");

	// FPS GameObject
	auto pFPS = pScene.CreateGameObject();
	pFPS->GetTransform()->SetLocalPosition(10, 10);
	pFPS->AddComponent<sgam::TextureComponent>();
	auto pFPSTextComp = pFPS->AddComponent<sgam::TextComponent>();
	const auto& pMediumFont = resourceManager.LoadFont("Lingua.otf", 18);
	pFPSTextComp->SetFont(pMediumFont);
	pFPS->AddComponent<sgam::FPSComponent>();

	// Controller GameObject
	auto pController = pScene.CreateGameObject();
	pController->GetTransform()->SetLocalPosition(100, 300);
	auto pCharacter1TextureComp = pController->AddComponent<sgam::TextureComponent>();
	const auto& pCharacter1Texture = resourceManager.LoadTexture("Character1.png");
	pCharacter1TextureComp->SetTexture(pCharacter1Texture);
	auto pControllerMoveComp = pController->AddComponent<sgam::MoveComponent>();
	pControllerMoveComp->SetMovementSpeed(100.f);
	auto pControllerPlayerComp = pController->AddComponent<sgam::PlayerComponent>();

	// Controller Move Commands
	inputManager.BindControllerCommand(
		0, sgam::InputManager::ControllerButton::DPAD_UP, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<sgam::MoveCommand>(pController, glm::vec2{ 0.f, -1.f })
	);
	inputManager.BindControllerCommand(
		0, sgam::InputManager::ControllerButton::DPAD_RIGHT, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<sgam::MoveCommand>(pController, glm::vec2{ 1.f, 0.f })
	);
	inputManager.BindControllerCommand(
		0, sgam::InputManager::ControllerButton::DPAD_DOWN, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<sgam::MoveCommand>(pController, glm::vec2{ 0.f, 1.f })
	);
	inputManager.BindControllerCommand(
		0, sgam::InputManager::ControllerButton::DPAD_LEFT, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<sgam::MoveCommand>(pController, glm::vec2{ -1.f, 0.f })
	);

	// Controller Observer Commands
	inputManager.BindControllerCommand(
		0, sgam::InputManager::ControllerButton::LEFT_SHOULDER, sgam::InputManager::InputType::ButtonDown,
		std::make_unique<sgam::FunctionCommand>(std::bind(&sgam::PlayerComponent::KillPlayer, pControllerPlayerComp))
	);
	inputManager.BindControllerCommand(
		0, sgam::InputManager::ControllerButton::RIGHT_SHOULDER, sgam::InputManager::InputType::ButtonDown,
		std::make_unique<sgam::FunctionCommand>(std::bind(&sgam::PlayerComponent::KillEnemy, pControllerPlayerComp))
	);

	// Controller Controls GameObject
	auto pControllerControls = pScene.CreateGameObject();
	pControllerControls->GetTransform()->SetLocalPosition(10, 120);
	pControllerControls->AddComponent<sgam::TextureComponent>();
	auto pControllerControlsTextComp = pControllerControls->AddComponent<sgam::TextComponent>();
	const auto& pSmallFont = resourceManager.LoadFont("Lingua.otf", 14);
	pControllerControlsTextComp->SetFont(pSmallFont);
	pControllerControlsTextComp->SetText("Use the D-Pad to move DigDug, Left shoulder to inflict damage, Right shoulder to increase score");

	// Controller Lives GameObject
	auto pControllerLives = pScene.CreateGameObject();
	pControllerLives->GetTransform()->SetLocalPosition(10, 170);
	pControllerLives->AddComponent<sgam::TextureComponent>();
	auto pControllerLivesTextComp = pControllerLives->AddComponent<sgam::TextComponent>();
	pControllerLivesTextComp->SetFont(pSmallFont);
	auto pControllerLivesComp = pControllerLives->AddComponent<sgam::LivesComponent>();
	pControllerLivesComp->SetLives(pControllerPlayerComp->GetHealth());
	pControllerPlayerComp->OnPlayerDied->AddObserver(pControllerLivesComp);

	// Controller Score GameObject
	auto pControllerScore = pScene.CreateGameObject();
	pControllerScore->GetTransform()->SetLocalPosition(10, 190);
	pControllerScore->AddComponent<sgam::TextureComponent>();
	auto pControllerScoreTextComp = pControllerScore->AddComponent<sgam::TextComponent>();
	pControllerScoreTextComp->SetFont(pSmallFont);
	auto pControllerScoreComp = pControllerScore->AddComponent<sgam::ScoreComponent>();
	pControllerPlayerComp->OnEnemyKilled->AddObserver(pControllerScoreComp);

	// Keyboard GameObject
	auto pKeyboard = pScene.CreateGameObject();
	pKeyboard->GetTransform()->SetLocalPosition(100, 400);
	auto pCharacter2TextureComp = pKeyboard->AddComponent<sgam::TextureComponent>();
	const auto& pCharacter2Texture = resourceManager.LoadTexture("Character2.png");
	pCharacter2TextureComp->SetTexture(pCharacter2Texture);
	auto pKeyboardMoveComp = pKeyboard->AddComponent<sgam::MoveComponent>();
	pKeyboardMoveComp->SetMovementSpeed(50.f);
	auto pKeyboardPlayerComp = pKeyboard->AddComponent<sgam::PlayerComponent>();

	// Keyboard Move Commands
	inputManager.BindKeyboardCommand(
		SDL_SCANCODE_W, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<sgam::MoveCommand>(pKeyboard, glm::vec2{ 0.f, -1.f })
	);
	inputManager.BindKeyboardCommand(
		SDL_SCANCODE_D, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<sgam::MoveCommand>(pKeyboard, glm::vec2{ 1.f, 0.f })
	);
	inputManager.BindKeyboardCommand(
		SDL_SCANCODE_S, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<sgam::MoveCommand>(pKeyboard, glm::vec2{ 0.f, 1.f })
	);
	inputManager.BindKeyboardCommand(
		SDL_SCANCODE_A, sgam::InputManager::InputType::ButtonPressed,
		std::make_unique<sgam::MoveCommand>(pKeyboard, glm::vec2{ -1.f, 0.f })
	);

	// Keyboard Observer Commands
	inputManager.BindKeyboardCommand(
		SDL_SCANCODE_LSHIFT, sgam::InputManager::InputType::ButtonDown,
		std::make_unique<sgam::FunctionCommand>(std::bind(&sgam::PlayerComponent::KillPlayer, pKeyboardPlayerComp))
	);
	inputManager.BindKeyboardCommand(
		SDL_SCANCODE_SPACE, sgam::InputManager::InputType::ButtonDown,
		std::make_unique<sgam::FunctionCommand>(std::bind(&sgam::PlayerComponent::KillEnemy, pKeyboardPlayerComp))
	);

	// Keyboard Controls GameObject
	auto pKeyboardControls = pScene.CreateGameObject();
	pKeyboardControls->GetTransform()->SetLocalPosition(10, 140);
	pKeyboardControls->AddComponent<sgam::TextureComponent>();
	auto pKeyboardControlsTextComp = pKeyboardControls->AddComponent<sgam::TextComponent>();
	pKeyboardControlsTextComp->SetFont(pSmallFont);
	pKeyboardControlsTextComp->SetText("Use WASD to move Fygar, Left shift to inflict damage, Space to increase score --> STEAM");

	// Keyboard Lives GameObject
	auto pKeyboardLives = pScene.CreateGameObject();
	pKeyboardLives->GetTransform()->SetLocalPosition(10, 210);
	pKeyboardLives->AddComponent<sgam::TextureComponent>();
	auto pKeyboardLivesTextComp = pKeyboardLives->AddComponent<sgam::TextComponent>();
	pKeyboardLivesTextComp->SetFont(pSmallFont);
	auto pKeyboardLivesComp = pKeyboardLives->AddComponent<sgam::LivesComponent>();
	pKeyboardLivesComp->SetLives(pKeyboardPlayerComp->GetHealth());
	pKeyboardPlayerComp->OnPlayerDied->AddObserver(pKeyboardLivesComp);

	// Keyboard Score GameObject
	auto pKeyboardScore = pScene.CreateGameObject();
	pKeyboardScore->GetTransform()->SetLocalPosition(10, 230);
	pKeyboardScore->AddComponent<sgam::TextureComponent>();
	auto pKeyboardScoreTextComp = pKeyboardScore->AddComponent<sgam::TextComponent>();
	pKeyboardScoreTextComp->SetFont(pSmallFont);
	auto pKeyboardScoreComp = pKeyboardScore->AddComponent<sgam::ScoreComponent>();
	pKeyboardPlayerComp->OnEnemyKilled->AddObserver(pKeyboardScoreComp);
	auto pKeyboardScoreAchievementComp = pKeyboardScore->AddComponent<sgam::AchievementUnlocker>();
	pKeyboardScoreComp->OnScoreChanged->AddObserver(pKeyboardScoreAchievementComp);
}

int main(int, char*[]) {
	sgam::Engine engine("../Data/");
	engine.Run(load);
    return 0;
}