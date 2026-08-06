#pragma once

#include "Font.h"
#include "Vector3.h"
#include "Renderer.h"
#include "Resource.h"

namespace gl
{
	class Renderer;

	class Text
	{
	public:
		Text() = default;
		Text(res_t<Font> font) : m_font{ font } {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(const Renderer& renderer, float x, float y);

	private:
		res_t<Font> m_font;
		SDL_Texture* m_texture{ nullptr };
	};
}