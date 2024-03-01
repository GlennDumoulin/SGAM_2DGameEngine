#pragma once
#include "RenderableComponent.h"

namespace sgam
{
	class Texture2D;

	class TextureComponent final : public RenderableComponent
	{
	public:
		virtual void Render() const override;

		void SetTexture(std::shared_ptr<Texture2D> pTexture) { m_pTexture = pTexture; }

		TextureComponent(GameObject* pOwner) : RenderableComponent(pOwner) {}
		~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}
