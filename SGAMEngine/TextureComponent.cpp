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
	const auto& rot{ GetTransform()->GetWorldRotation() };
	const auto& scale{ GetTransform()->GetWorldScale() };

	SDL_Rect dst{};
	dst.x = static_cast<int>(pos.x) + m_DstOffset.x;
	dst.y = static_cast<int>(pos.y) + m_DstOffset.y;

	// Check if we have a valid destination rect
	if (m_DstSize.x == 0 || m_DstSize.y == 0)
	{
		// If not, render with srcRect
		dst.w = static_cast<int>(m_SrcRect.w * scale.x);
		dst.h = static_cast<int>(m_SrcRect.h * scale.y);
	}
	else
	{
		// If so, render with dstRect
		dst.w = static_cast<int>(m_DstSize.x * scale.x);
		dst.h = static_cast<int>(m_DstSize.y * scale.y);
	}

	Renderer::GetInstance().RenderTexture(*m_pTexture, &m_SrcRect, &dst, rot);
}

void sgam::TextureComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	// Set new texture
	m_pTexture = pTexture;

	// Set new source rect
	const glm::ivec2 size{ GetTextureSize() };
	m_SrcRect = SDL_Rect{ 0, 0, size.x, size.y };
}

void sgam::TextureComponent::SetDstOffset(const glm::vec2 offset)
{
	// Set new destination position
	m_DstOffset.x = static_cast<int>(offset.x);
	m_DstOffset.y = static_cast<int>(offset.y);
}

void sgam::TextureComponent::SetDstSize(int width, int height)
{
	// Set new destination size
	m_DstSize.x = width;
	m_DstSize.y = height;
}

const glm::ivec2 TextureComponent::GetTextureSize() const
{
	// Check if we have a texture to get the size from
	if (!m_pTexture)
	{
		std::cout << "Can't get texture size because there is no texture!\n";
		return glm::ivec2{ 0, 0 };
	}

	// Check if we have a valid destination size
	if (m_DstSize.x != 0 && m_DstSize.y != 0)
	{
		return m_DstSize;
	}

	// If not, return default texture size
	return m_pTexture->GetSize();
}
