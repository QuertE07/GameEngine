#pragma once

#include "SpriteRendererComponent.h"
#include "Resources/Resource.h"

namespace gl
{
	class SpriteAnimationRendererComponent : public SpriteRendererComponent
	{
	public:
		CLASS_PROTOTYPE(SpriteAnimationRendererComponent)

		void Update(float dt) override;
		void Draw(const Renderer& renderer) override;

		virtual void Read(const json::value_t& value) override;

	protected:
		float m_framesPerSecond = 1.0f;
		bool m_loop = true;

		unsigned int m_frame = 0;
		float m_frameTimer = 0;

		res_t<class TextureFrames> m_textureFrames;
	};
}