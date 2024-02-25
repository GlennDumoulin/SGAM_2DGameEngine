#pragma once
#include <string>
#include <memory>

#include "Component.h"

namespace sgam
{
	class Font;
	class Texture2D;

	class TextComponent final : public Component
	{
	public:
		virtual void Update() override;

		virtual void Render() const override;

		void SetFont(std::shared_ptr<Font> pFont);
		void SetText(const std::string& text);

		TextComponent() = default;
		~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		std::string m_Text;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_TextTexture;

		bool m_NeedsUpdate;
	};
}
