#include <stdexcept>
#include <SDL_ttf.h>

#include "Font.h"

using namespace sgam;

Font::Font(const std::string& fullPath, unsigned int size) : m_pFont(nullptr)
{
	m_pFont = TTF_OpenFont(fullPath.c_str(), size);
	if (m_pFont == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

Font::~Font()
{
	TTF_CloseFont(m_pFont);
}

TTF_Font* Font::GetFont() const
{
	return m_pFont;
}
