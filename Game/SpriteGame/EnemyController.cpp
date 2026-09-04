#include "EnemyController.h"
#include "PlayerController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Engine.h"
#include "Damager.h"
#include "SpriteGame.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Start()
{
	CharacterBase::Start();

	m_physicsComponent = GetComponent<gl::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<gl::SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void EnemyController::Update(float dt)
{
	gl::Vector2 velocity = m_physicsComponent->GetVelocity();

	switch (m_state)
	{
	case CharacterBase::State::Move:
	{
		int dir = 0;

		auto player = m_scene->GetActorByName<Actor>("PlayerPrototype");
		if (player)
		{
			gl::Vector2 position = m_physicsComponent->GetPosition();
			gl::Vector2 playerPosition = player->GetTransform().position;

			dir = (playerPosition.x > position.x) - (playerPosition.x < position.x);

			if (dir != 0)
			{
				velocity.x = dir * 50.0f;
				m_rendererComponent->Play("walk");
				m_rendererComponent->SetFlipH((dir < 0) ? true : false);
			}
			else
			{
				m_rendererComponent->Play("idle");
			}

			if (position.Distance(playerPosition) < 120)
			{
				m_state = State::Attack;
				m_rendererComponent->Play("attack");
				m_hasAttacked = false;
			}
		}
	}
		break;
	case CharacterBase::State::Attack:
		if (m_rendererComponent->GetFrame() == 7 && !m_hasAttacked)
		{
			auto damager = gl::Factory::Instance().Create<Damager>("DamagerPrototype");
			damager->SetTag("EnemyDamager");
			damager->SetPosition(GetTransform().position + gl::Vector2{ 100.0f * ((m_rendererComponent->GetFlipH()) ? -1 : 1), 0.0f });
			damager->SetScale(3);
			damager->SetDamage(2);
			m_scene->AddActor(std::move(damager));
			m_hasAttacked = true;
		}

		if (m_rendererComponent->IsAnimationDone())
		{
			m_state = State::Move;
			m_rendererComponent->Play("idle");
		}
		break;
	case CharacterBase::State::Hit:
		if (m_rendererComponent->IsAnimationDone())
		{
			m_state = State::Move;
			m_rendererComponent->Play("idle");
		}
		break;
	case CharacterBase::State::Death:
		if (m_rendererComponent->IsAnimationDone())
		{
			SetDestroyed();
		}
		break;
	default:
		break;
	}

	

	if (false)
	{
		velocity.y = -500.0f;
	}

	

	m_physicsComponent->SetVelocity(velocity);

	CharacterBase::Update(dt);
}

void EnemyController::OnCollision(gl::Actor* other)
{
	if (other->GetTag() == "PlayerDamager" && m_state != State::Death)
	{
		other->SetDestroyed();

		m_state = State::Hit;
		m_rendererComponent->Play("hit");
		Damager* damager = dynamic_cast<Damager*>(other);
		if (damager) {
			m_health -= damager->GetDamage();
		}
		if (m_health <= 0.0f)
		{
			m_rendererComponent->Play("death");
			m_state = State::Death;
			auto game = dynamic_cast<SpriteGame*>(m_scene->GetGame());
			game->AddPoints(200);
		}

		other->SetDestroyed();
	}
}

void EnemyController::Read(const gl::json::value_t& value)
{
	CharacterBase::Read(value);
}
