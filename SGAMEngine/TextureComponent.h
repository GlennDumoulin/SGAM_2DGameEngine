#pragma once
#include <SDL.h>
#include <glm/glm.hpp>

#include "RenderableComponent.h"

namespace sgam
{
	class Texture2D;

	class TextureComponent final : public RenderableComponent
	{
	public:
		virtual void Render() const override;

		void SetTexture(std::shared_ptr<Texture2D> pTexture);

		void SetDstOffset(const glm::vec2 offset);
		void SetDstSize(int width, int height);

		const glm::ivec2 GetTextureSize() const;

		explicit TextureComponent(GameObject* pOwner) : RenderableComponent(pOwner) {}
		~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};

		SDL_Rect m_SrcRect{};

		glm::ivec2 m_DstOffset{};
		glm::ivec2 m_DstSize{};
	};
}
