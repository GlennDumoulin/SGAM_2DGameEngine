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
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "Transform.h"
#include "Scene.h"

void load()
{
	auto& scene = sgam::SceneManager::GetInstance().CreateScene("Demo");

	// Background GameObject
	const auto& pBackground = std::make_shared<sgam::GameObject>();
	auto pBackgroundTextureComp = pBackground->AddComponent<sgam::TextureComponent>();
	const auto& pBackgroundTexture = sgam::ResourceManager::GetInstance().LoadTexture("background.tga");
	pBackgroundTextureComp->SetTexture(pBackgroundTexture);
	scene.Add(pBackground);

	// Logo GameObject
	const auto& pLogo = std::make_shared<sgam::GameObject>();
	pLogo->GetTransform()->SetPosition(216, 180, 0);
	auto pLogoTextureComp = pLogo->AddComponent<sgam::TextureComponent>();
	const auto& pLogoTexture = sgam::ResourceManager::GetInstance().LoadTexture("logo.tga");
	pLogoTextureComp->SetTexture(pLogoTexture);
	scene.Add(pLogo);

	// Text GameObject
	const auto& pText = std::make_shared<sgam::GameObject>();
	pText->GetTransform()->SetPosition(80, 20, 0);
	auto pTextComp = pText->AddComponent<sgam::TextComponent>();
	const auto& pTextFont = sgam::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	pTextComp->SetFont(pTextFont);
	pTextComp->SetText("Programming 4 Assignment");
	scene.Add(pText);

	// FPS GameObject
	const auto& pFPS = std::make_shared<sgam::GameObject>();
	pFPS->GetTransform()->SetPosition(10, 10, 0);
	auto pFPSComp = pFPS->AddComponent<sgam::FPSComponent>();
	const auto& pFPSFont = sgam::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	pFPSComp->SetFont(pFPSFont);
	scene.Add(pFPS);
}

int main(int, char*[]) {
	sgam::Engine engine("../Data/");
	engine.Run(load);
    return 0;
}