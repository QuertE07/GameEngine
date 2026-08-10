#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtils.h"

#include "AnimatedModel.h"

namespace gl
{
    void Actor::Update(float dt)
    {
        if (m_lifespan > 0.0f) {
            m_lifespan -= dt;
            m_destroyed = (m_lifespan <= 0.0f);
        }

        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.9f;
    }

    void Actor::Draw(const Renderer& renderer) const
    {
        renderer.DrawTexture(*m_sprite.get(), m_transform.position.x, m_transform.position.y, m_transform.rotation, m_transform.scale);
    }

    float Actor::GetRadius() const
    {
        return (m_sprite->GetSize().x * 0.5 + m_sprite->GetSize().y * 0.5) * m_transform.scale * 0.45f;
    }
}