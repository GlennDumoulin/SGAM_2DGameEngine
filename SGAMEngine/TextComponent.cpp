#include <stdexcept>
#include <iostream>

#include "TextComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

using namespace sgam;

void TextComponent::Update()
{
	// Don't update if nothing changed
	if (m_HasChanged)
	{
		// Check if there is a font assigned, if not don't update
		if (!m_pFont)
		{
			std::cout << "TextComponent needs an assigned Font\n";
			return;
		}

		// Check if there is a TextureComponent on the owning GameObject, if not don't update
		if (!m_pTextureComponent)
		{
			m_pTextureComponent = GetOwner()->GetComponent<TextureComponent>();

			if (!m_pTextureComponent)
			{
				std::cout << "TextComponent can't render without TextureComponent\n";
				return;
			}
		}

		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);

		// Set the new texture in the TextureComponent
		m_pTextureComponent->SetTexture(std::make_shared<Texture2D>(texture));

		// Reset needsUpdate back to false
		m_HasChanged = false;
	}
}

void TextComponent::SetFont(std::shared_ptr<Font> pFont)
{
	// Don't update if nothing changed
	if (m_pFont.get() == pFont.get()) return;

	m_pFont = pFont;
	m_HasChanged = true;
}

void TextComponent::SetText(const std::string& text)
{
	// Don't update if nothing changed
	if (m_Text == text) return;

	// Make sure we don't set an empty string
	if (text.empty())
	{
		std::cout << "TextComponent can't set an empty text. Consider setting IsEnabled to false\n";
		return;
	}

	m_Text = text;
	m_HasChanged = true;
}

void TextComponent::SetColor(const SDL_Color& color)
{
	// Don't update if nothing changed
	if (m_Color.r == color.r && m_Color.g == color.g && m_Color.b == color.b && m_Color.a == color.a) return;

	m_Color = color;
	m_HasChanged = true;
}

void TextComponent::SetColor(const Uint8 r, const Uint8 g, const Uint8 b)
{
	// Don't update if nothing changed
	if (m_Color.r == r && m_Color.g == g && m_Color.b == b && m_Color.a == UINT8_MAX) return;

	m_Color = SDL_Color{ r, g, b, UINT8_MAX };
	m_HasChanged = true;
}

void TextComponent::SetColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
	// Don't update if nothing changed
	if (m_Color.r == r && m_Color.g == g && m_Color.b == b && m_Color.a == a) return;

	m_Color = SDL_Color{ r, g, b, a };
	m_HasChanged = true;
}
