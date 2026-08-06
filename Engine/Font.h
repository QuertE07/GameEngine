#pragma once

#include "Resource.h"

#include <SDL3_ttf/SDL_ttf.h>
#include<string>

struct TTF_Font;

namespace gl
{
	class Font : public Resource
	{
	public:
		Font() = default;
		~Font();

		bool Load(const std::string& name, float fontSize);

	private:
		friend class Text;

		TTF_Font* m_ttfFont{ nullptr };
	};
}