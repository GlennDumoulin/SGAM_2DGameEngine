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

void ScenesSetup()
{
	auto& sceneManager{ sgam::SceneManager::GetInstance() };

	// Create the needed scenes
	sceneManager.CreateScene(digdug::DemoScene::Load, "DemoScene");
	sceneManager.CreateScene(digdug::GameScene::Load, "GameScene");

	// Set the initial scene
	sceneManager.SetNextScene("GameScene");
}

int main(int, char* [])
{
	sgam::Engine engine{ "../Data/", 480, 580 };

	ScenesSetup();

	engine.Run();

	return 0;
}
