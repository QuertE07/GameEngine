#pragma once

#include "Vector2.h"
#include <string>

struct SDL_Texture;

namespace gl
{

	class Texture
	{
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, class Renderer& renderer);

		Vector2 GetSize();

		friend class Renderer;

	private:
		SDL_Texture* m_texture{ nullptr };
	};
}