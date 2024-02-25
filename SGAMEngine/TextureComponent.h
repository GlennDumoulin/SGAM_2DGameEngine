#pragma once
#include <memory>

#include "Component.h"
#include "Texture2D.h"

namespace sgam
{
	class TextureComponent final : public Component
	{
	public:
		virtual void Render() const override;

		void SetTexture(std::shared_ptr<Texture2D> pTexture) { m_pTexture = pTexture; }

		TextureComponent() = default;
		~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}
