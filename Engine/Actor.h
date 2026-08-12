#pragma once

#include "Object.h"
#include "Transform.h"
#include "Texture.h"
#include <string>

namespace gl
{
    class Scene;

    struct ActorDesc
    {
        std::string name;
        std::string tag;
        Transform transform {};
        Vector2 velocity = { 0.0f, 0.0f };
        std::shared_ptr<Texture> sprite;
    };

    class Actor : public Object
    {
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) :
            m_tag{ actorDesc.tag },
            m_transform{ actorDesc.transform },
            m_velocity{ actorDesc.velocity },
            m_sprite{ actorDesc.sprite }
        {}

        Actor(const Transform& transform, const std::shared_ptr<Texture> sprite) : m_transform{ transform }, m_sprite{ sprite } {}

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

        void Read(const json::value_t& value);

        void SetDestroyed(bool destroy = true) { m_destroyed = destroy; }
        bool GetDestroyed() const { return m_destroyed; }

        friend Scene;

    protected:
        std::string m_tag;

        Transform m_transform;
        Vector2 m_velocity{ 0.0f, 0.0f };
        float m_damping{ 0.0f };
        float m_lifespan{ 0 };
        bool m_destroyed{ false };

        std::shared_ptr<Texture> m_sprite;
        Scene* m_scene = nullptr;
    };
}