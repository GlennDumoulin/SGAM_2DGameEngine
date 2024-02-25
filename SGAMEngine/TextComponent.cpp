#include <stdexcept>
#include <SDL_ttf.h>

#include "Transform.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

using namespace sgam;

void TextComponent::Update()
{
	// Don't update if nothing changed
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
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
		m_TextTexture = std::make_shared<Texture2D>(texture);

		// Reset needsUpdate back to false
		m_NeedsUpdate = false;
	}
}

void TextComponent::Render() const
{
	if (m_TextTexture)
	{
		const auto& pos = GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

void TextComponent::SetFont(std::shared_ptr<Font> pFont)
{
	// Don't update if nothing changed
	if (m_pFont.get() == pFont.get()) return;

	m_pFont = pFont;
	m_NeedsUpdate = true;
}

// This implementation uses the "dirty flag" pattern
void TextComponent::SetText(const std::string& text)
{
	// Don't update if nothing changed
	if (text == m_Text) return;

	m_Text = text;
	m_NeedsUpdate = true;
}
