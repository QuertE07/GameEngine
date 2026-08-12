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

    void Actor::Read(const json::value_t& value)
    {
        Object::Read(value);

        if (JSON_HAS_NAME(value, "transform"))
        {
            m_transform.Read(JSON_GET_NAME(value, "transform"));
        }

        JSON_READ_NAME(value, "tag", m_tag);
        JSON_READ_NAME(value, "lifespan", m_lifespan);
        JSON_READ_NAME(value, "velocity", m_velocity);
        JSON_READ_NAME(value, "damping", m_damping);
    }
}