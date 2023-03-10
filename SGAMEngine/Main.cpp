#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Engine.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TextObject.h"
#include "Scene.h"

void load()
{
	auto& scene = sgam::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<sgam::GameObject>();
	go->SetTexture("background.tga");
	scene.Add(go);

	auto font = sgam::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<sgam::TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	go->AddComponent(to);

	go = std::make_shared<sgam::GameObject>();
	go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);
}

int main(int, char*[]) {
	sgam::Engine engine("../Data/");
	engine.Run(load);
    return 0;
}