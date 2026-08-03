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

    Enemy(float speed, const gl::Transform& transform) :
        Actor{ transform },
        m_speed{ speed }
    { }

    Enemy(float speed, const gl::Transform& transform, const gl::AnimatedModel& model) :
        Actor{ transform, model },
        m_speed{ speed }
    { }

    void Update(float dt) override;

    void OnCollision(Actor* other) override;

private:
    int m_ammo = 0;
    float m_speed = 800.0f;

};