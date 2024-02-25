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
#include "Transform.h"
#include "Scene.h"

void load()
{
	auto& scene = sgam::SceneManager::GetInstance().CreateScene("Demo");

	// Background GameObject
	const auto& pBackground = std::make_shared<sgam::GameObject>();
	const auto& pBackgroundTextureComp = pBackground->AddComponent<sgam::TextureComponent>();
	const auto& pBackgroundTexture = sgam::ResourceManager::GetInstance().LoadTexture("background.tga");
	pBackgroundTextureComp->SetTexture(pBackgroundTexture);
	scene.Add(pBackground);

	// Logo GameObject
	const auto& pLogo = std::make_shared<sgam::GameObject>();
	pLogo->GetTransform()->SetPosition(216, 180, 0);
	const auto& pLogoTextureComp = pLogo->AddComponent<sgam::TextureComponent>();
	const auto& pLogoTexture = sgam::ResourceManager::GetInstance().LoadTexture("logo.tga");
	pLogoTextureComp->SetTexture(pLogoTexture);
	scene.Add(pLogo);

	// Text GameObject
	const auto& pText = std::make_shared<sgam::GameObject>();
	pText->GetTransform()->SetPosition(80, 20, 0);
	const auto& pTextComp = pText->AddComponent<sgam::TextComponent>();
	const auto& pFont = sgam::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	pTextComp->SetFont(pFont);
	pTextComp->SetText("Programming 4 Assignment");
	scene.Add(pText);
}

int main(int, char*[]) {
	sgam::Engine engine("../Data/");
	engine.Run(load);
    return 0;
}