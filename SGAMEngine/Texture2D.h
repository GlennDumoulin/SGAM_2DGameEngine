#pragma once
#include <glm/vec2.hpp>

struct SDL_Texture;

namespace sgam
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D final
	{
	public:
		SDL_Texture* GetSDLTexture() const;

		glm::ivec2 GetSize() const;

		explicit Texture2D(SDL_Texture* pTexture);
		~Texture2D();
		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

	private:
		SDL_Texture* m_pTexture;
	};
}
