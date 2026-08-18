#pragma once
#include "RendererComponent.h"
#include "Texture.h"

namespace gl
{
	class SpriteRendererComponent : public RendererComponent
	{
	public:
		CLASS_PROTOTYPE(SpriteRendererComponent)

		void Draw(const Renderer& renderer) override;

		virtual void Read(const json::value_t& value) override;

	protected:
		res_t<Texture> m_texture;
	};
}