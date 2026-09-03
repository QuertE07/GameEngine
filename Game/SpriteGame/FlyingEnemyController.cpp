#include "FlyingEnemyController.h"
#include "PlayerController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Engine.h"
#include "Damager.h"

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start()
{
	CharacterBase::Start();

	m_physicsComponent = GetComponent<gl::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<gl::SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void FlyingEnemyController::Update(float dt)
{
	switch (m_state)
	{
	case CharacterBase::State::Move:
	{
		auto player = m_scene->GetActorByName<Actor>("PlayerPrototype");
		if (player)
		{
			gl::Vector2 position = m_physicsComponent->GetPosition();
			gl::Vector2 playerPosition = player->GetTransform().position;

			gl::Vector2 direction = (playerPosition - position).Normalized();

			m_physicsComponent->ApplyForce(direction * 400.0f);

			m_rendererComponent->SetFlipH((direction.x < 0) ? true : false);

			if (position.Distance(playerPosition) < 40)
			{
				std::cout << "here" << std::endl;
				m_state = State::Attack;
				m_rendererComponent->Play("attack");
				m_hasAttacked = false;
			}
		}
	}
		break;
	case CharacterBase::State::Attack:
		if (m_rendererComponent->GetFrame() == 6 && !m_hasAttacked)
		{
			auto damager = gl::Factory::Instance().Create<Damager>("DamagerPrototype");
			damager->SetPosition(GetTransform().position);
			damager->SetDamage(1);
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
		break;
	default:
		break;
	}

	CharacterBase::Update(dt);
}

void FlyingEnemyController::OnCollision(gl::Actor* other)
{
	if (other->GetTag() == "PlayerDamager")
	{
		m_state = State::Hit;
		m_rendererComponent->Play("hit");
		Damager* damager = dynamic_cast<Damager*>(other);
		if (damager) m_health -= damager->GetDamage();
		std::cout << "HitEnemy" << std::endl;
		if (m_health <= 0.0f)
		{
			SetDestroyed();
		}

		other->SetDestroyed();
	}
}

void FlyingEnemyController::Read(const gl::json::value_t& value)
{
	CharacterBase::Read(value);
}
