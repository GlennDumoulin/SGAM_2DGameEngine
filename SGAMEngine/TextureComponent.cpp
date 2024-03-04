#include "TextureComponent.h"
#include "Renderer.h"
#include "Transform.h"

using namespace sgam;

void TextureComponent::Render() const
{
	// Check if we have a texture to render
	if (!m_pTexture) return;

	const auto& pos{ GetTransform()->GetWorldPosition() };
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}
