#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Engine.h"

#include "SceneManager.h"
#include "DemoScene.h"
#include "GameScene.h"
#include "MenuScene.h"

#include "ServiceLocator.h"
#include "SDLSoundSystem.h"
#include "DebugSoundSystem.h"

static void ScenesSetup()
{
	auto& sceneManager{ sgam::SceneManager::GetInstance() };

	// Create the needed scenes
	sceneManager.CreateScene(digdug::DemoScene::Load, "DemoScene");
	sceneManager.CreateScene(digdug::GameScene::Load, "GameScene");
	sceneManager.CreateScene(digdug::MenuScene::Load, "MenuScene");

	// Set the initial scene
	sceneManager.SetNextScene("MenuScene");
}

static void RegisterSoundSystem()
{
	// Register SoundSystem
#if _DEBUG
	sgam::ServiceLocator::RegisterSoundSystem(
		std::make_unique<sgam::DebugSoundSystem>(std::make_unique<sgam::SDLSoundSystem>())
	);
#else
	sgam::ServiceLocator::RegisterSoundSystem(std::make_unique<sgam::SDLSoundSystem>());
#endif
}

int main(int, char* [])
{
	sgam::Engine engine{ "../Data/", 480, 580 };

	ScenesSetup();
	RegisterSoundSystem();

	engine.Run();

	return 0;
}
