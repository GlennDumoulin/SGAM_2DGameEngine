#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Engine.h"

#include "SceneManager.h"
#include "DemoScene.h"

void ScenesSetup()
{
	auto& sceneManager{ sgam::SceneManager::GetInstance() };

	// Create the needed scenes
	sceneManager.CreateScene(digdug::DemoScene::Load, "DemoScene");

	// Set the initial scene
	sceneManager.SetNextScene("DemoScene");
}

int main(int, char* [])
{
	sgam::Engine engine{ "../Data/" };

	ScenesSetup();

	engine.Run();

	return 0;
}
