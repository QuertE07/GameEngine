#pragma once

#include "Font.h"
#include "Vector3.h"
#include "Renderer.h"

namespace gl
{
	class Text {
	public:
		Text() = default;
		Text(Font* font) : m_font{ font } {}
		~Text();

		bool Create(const Renderer& renderer, const std::string& text, const Color& color);
		void Draw(const Renderer& renderer, float x, float y);

	private:
		Font* m_font = nullptr;
		SDL_Texture* m_texture = nullptr;
	};
}