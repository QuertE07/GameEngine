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
        renderer.DrawModel(m_model, m_transform);
    }

    float Actor::GetRadius() const
    {
        return m_model.GetRadius() * m_transform.scale * 0.9f;
    }
}