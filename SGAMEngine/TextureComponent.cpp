#include <iostream>

#include "TextureComponent.h"
#include "Renderer.h"
#include "Transform.h"
#include "Texture2D.h"

using namespace sgam;

void TextureComponent::Render() const
{
	// Check if we have a texture to render
	if (!m_pTexture) return;

	const auto& pos{ GetTransform()->GetWorldPosition() };
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

const glm::ivec2 TextureComponent::GetTextureSize() const
{
	// Check if we have a texture to get the size from
	if (!m_pTexture)
	{
		std::cout << "Can't get texture size because there is no texture!\n";
		return glm::ivec2{ 0, 0 };
	}

	return m_pTexture->GetSize();
}
