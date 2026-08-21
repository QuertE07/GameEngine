#include "pch.h"
#include "SpriteRendererComponent.h"
#include "Engine.h"

namespace gl
{
	FACTORY_REGISTER(SpriteRendererComponent)

	void SpriteRendererComponent::Draw(const Renderer& renderer)
	{
		if (m_texture)
		renderer.DrawTexture(*m_texture.get(),
			GetOwner()->GetTransform().position.x,
			GetOwner()->GetTransform().position.y,
			GetOwner()->GetTransform().rotation,
			GetOwner()->GetTransform().scale);
	}

	void SpriteRendererComponent::Read(const json::value_t& value)
	{
		Object::Read(value);

		std::string textureName;

		JSON_READ_NAME(value, "texture", textureName);
		if (!textureName.empty())
		{
			m_texture = Resources().Get<Texture>(textureName, Engine::Get().GetRenderer());
		}
	}
}