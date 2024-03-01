#pragma once
#include <string>
#include <memory>
#include <SDL_ttf.h>

#include "FunctionalComponent.h"
#include "TextureComponent.h"

namespace sgam
{
	class Font;

	class TextComponent final : public FunctionalComponent
	{
	public:
		virtual void Update() override;

		void SetFont(std::shared_ptr<Font> pFont);
		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);
		void SetColor(const Uint8 r, const Uint8 g, const Uint8 b);
		void SetColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);

		TextComponent(GameObject* pOwner) : FunctionalComponent(pOwner) {}
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		TextureComponent* m_pTextureComponent{};

		std::string m_Text{ " " };
		std::shared_ptr<Font> m_pFont{};
		SDL_Color m_Color{ 255, 255, 255, 255 }; // Default: white

		bool m_HasChanged{ false };
	};
}
