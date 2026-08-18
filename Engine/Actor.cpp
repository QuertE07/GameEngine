#include "pch.h"
#include "Actor.h"
#include "Engine.h" 
#include "Components/RendererComponent.h"

namespace gl
{
    FACTORY_REGISTER(Actor)

    void Actor::Update(float dt)
    {
        if (m_lifespan > 0.0f) {
            m_lifespan -= dt;
            m_destroyed = (m_lifespan <= 0.0f);
        }

        for (auto component : m_components)
        {
            component->Update(dt);
        }

        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.9f;
    }

    void Actor::Draw(const Renderer& renderer) const
    {
        for (auto component : m_components)
        {
            auto rendererComponent = dynamic_cast<RendererComponent*>(component);
            if (rendererComponent) rendererComponent->Draw(renderer);
        }
    }

    float Actor::GetRadius() const
    {
        //return (m_sprite->GetSize().x * 0.5 + m_sprite->GetSize().y * 0.5) * m_transform.scale * 0.45f;
        return 0.0f;
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

        if (JSON_HAS_NAME(value, "components"))
        {
            for (auto& componentValue : JSON_GET_NAME(value, "components").GetArray())
            {
                std::string typeName;
                JSON_READ_NAME(componentValue, "type", typeName);

                auto component = Factory::Instance().Create<Component>(typeName);
                if (component) component->Read(componentValue);
            }
        }
    }
}