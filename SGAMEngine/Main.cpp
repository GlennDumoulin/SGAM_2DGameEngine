#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Engine.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"

void load()
{
	auto& pScene = sgam::SceneManager::GetInstance().CreateScene("Demo");
	const auto& resourceManager = sgam::ResourceManager::GetInstance();

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
	const auto& pTextFont = resourceManager.LoadFont("Lingua.otf", 36);
	pTextComp->SetFont(pTextFont);
	pTextComp->SetText("Programming 4 Assignment");

	// FPS GameObject
	auto pFPS = pScene.CreateGameObject();
	pFPS->GetTransform()->SetLocalPosition(10, 10);
	pFPS->AddComponent<sgam::TextureComponent>();
	auto pFPSTextComp = pFPS->AddComponent<sgam::TextComponent>();
	const auto& pFPSFont = resourceManager.LoadFont("Lingua.otf", 18);
	pFPSTextComp->SetFont(pFPSFont);
	pFPS->AddComponent<sgam::FPSComponent>();
}

int main(int, char*[]) {
	sgam::Engine engine("../Data/");
	engine.Run(load);
    return 0;
}