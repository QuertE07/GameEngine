#pragma once

#include "Transform.h"
#include "AnimatedModel.h"
#include <string>

namespace gl
{
    class Scene;

    struct ActorDesc
    {
        std::string name;
        std::string tag;
        Transform transform;
        Vector2 velocity = { 0.0f, 0.0f };
        AnimatedModel model;
    };

    class Actor
    {
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) :
            m_name{ actorDesc.name },
            m_tag{ actorDesc.tag },
            m_transform{ actorDesc.transform },
            m_velocity{ actorDesc.velocity },
            m_model{ actorDesc.model }
        {
        }

        Actor(const Transform& transform) : m_transform{ transform } {}
        Actor(const Transform& transform, const AnimatedModel& model) : m_transform{ transform }, m_model{ model } {}

        virtual void Update(float dt);
        virtual void Draw(const class Renderer& renderer) const;

        virtual void OnCollision(Actor* other) {}

        const Transform& GetTransform() const { return m_transform; }
        void SetPosition(Vector2 position) { m_transform.position = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(float scale) { m_transform.scale = scale; }

        const Vector2& GetVelocity() const { return m_velocity; }
        void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }
        void AddVelocity(const Vector2& velocity) { m_velocity += velocity; }

        const std::string& GetName() const { return m_name; }
        const std::string& GetTag() const { return m_tag; }

        Scene* GetScene() { return m_scene; }

        float GetRadius() const;

        void SetDestroyed(bool destroy = true) { m_destroyed = destroy; }
        bool GetDestroyed() const { return m_destroyed; }

        friend Scene;

    protected:
        std::string m_name;
        std::string m_tag;

        Transform m_transform;
        Vector2 m_velocity{ 0.0f, 0.0f };
        float m_damping{ 0.0f };
        float m_lifespan{ 0 };
        bool m_destroyed{ false };

        AnimatedModel m_model;
        Scene* m_scene = nullptr;
    };
}