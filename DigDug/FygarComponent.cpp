#include "ResourceManager.h"

#include "GameObject.h"
#include "FygarComponent.h"
#include "TextureComponent.h"

using namespace digdug;

FygarComponent::FygarComponent(sgam::GameObject* pOwner)
	: sgam::FunctionalComponent(pOwner)
{
	// Set the wander texture
	const auto& pTexture{ sgam::ResourceManager::GetInstance().LoadTexture("Fygar/Default.png") };
	GetOwner()->GetComponent<sgam::TextureComponent>()->SetTexture(pTexture);
}

void FygarComponent::Update()
{
}
