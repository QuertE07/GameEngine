#include "Enemy.h"
#include "Player.h"
#include "Renderer/Renderer.h"
#include "Engine.h"

void Enemy::Update(float dt)
{
	Player* player = m_scene->GetActorByName<Player>("PlayerPrototype");
	if (player)
	{
		gl::Vector2 direction = player->GetTransform().position - m_transform.position;
		float rotation = direction.Angle();
		m_transform.rotation = rotation;

		gl::Vector2 forward{ 1, 0 };
		forward = forward.Rotate(m_transform.rotation * gl::DegToRad);
		//AddVelocity(forward * m_speed * dt);
	}

	float thrust = 0.0f;
	float rotate = 0.0f;

	gl::Vector2 forward{ 1, 0 };
	gl::Vector2 velocity = forward.Rotate(m_transform.rotation * gl::DegToRad) * thrust;
	//AddVelocity(velocity * dt);

	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other)
{
	if (other->GetTag() == "PlayerAttack")
	{
		m_destroyed = true;
	}
}
