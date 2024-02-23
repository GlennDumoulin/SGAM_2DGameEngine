#include <SDL.h>

#include "Texture2D.h"

using namespace sgam;

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

glm::ivec2 Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}

Texture2D::Texture2D(SDL_Texture* pTexture)
{
	m_pTexture = pTexture;
}
