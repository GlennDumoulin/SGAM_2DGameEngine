#pragma once
#include <string>
#include "BaseComponent.h"
#include "Transform.h"

namespace sgam
{
	class Font;
	class Texture2D;

	class TextObject final : public BaseComponent
	{
	public:
		TextObject(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;

		void Update() override;

		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

	private:
		bool m_needsUpdate;
		std::string m_text;
		Transform m_transform{};
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}
