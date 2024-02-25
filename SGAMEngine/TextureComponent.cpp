#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"

using namespace sgam;

void TextureComponent::Render() const
{
	const auto& pos{ GetTransform()->GetPosition() };
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}
