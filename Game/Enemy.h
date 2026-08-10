#pragma once
#include "Actor.h"

struct EnemyDesc : public gl::ActorDesc {
    float speed;
};

class Enemy : public gl::Actor {
public:
    Enemy() = default;
    Enemy(const EnemyDesc& enemyDesc) :
        Actor(enemyDesc),
        m_speed{ enemyDesc.speed }
    { }

    Enemy(float speed, const gl::Transform& transform, const std::shared_ptr<gl::Texture> sprite) :
        Actor{ transform, sprite },
        m_speed{ speed }
    { }

    void Update(float dt) override;

    void OnCollision(Actor* other) override;

private:
    int m_ammo = 0;
    float m_speed = 800.0f;

};