#include "PlayerController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Engine.h"
#include "Damager.h"
#include "SpriteGame.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::Start()
{
	CharacterBase::Start();

	m_physicsComponent = GetComponent<gl::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<gl::SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void PlayerController::Update(float dt)
{
	gl::Vector2 velocity = m_physicsComponent->GetVelocity();

	switch (m_state)
	{
	case CharacterBase::State::Move:
	{
		int dir = (gl::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) - (gl::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LEFT));
		if (gl::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_Z))
		{
			velocity.y = -500.0f;
		}

		if (dir != 0)
		{
			velocity.x = dir * 200.0f;
			m_rendererComponent->Play("run");
			m_rendererComponent->SetFlipH((dir < 0) ? true : false);
		}
		else
		{
			m_rendererComponent->Play("idle");
		}

		if (gl::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_X))
		{
			m_state = State::Attack;
			m_rendererComponent->Play("attack");
			m_hasAttacked = false;
		}

		if (m_physicsComponent->GetPosition().y > 2000.0f)
		{
			m_rendererComponent->Play("death");
			m_state = State::Death;
			auto game = dynamic_cast<SpriteGame*>(m_scene->GetGame());
			game->LifeLost();
		}
	}
		break;
	case CharacterBase::State::Attack:
	{
		if (m_rendererComponent->GetFrame() == 3 && !m_hasAttacked)
		{
			auto damager = gl::Factory::Instance().Create<Damager>("DamagerPrototype");
			damager->SetPosition(GetTransform().position + gl::Vector2{ 60.0f * ((m_rendererComponent->GetFlipH()) ? -1 : 1), 0.0f});
			damager->SetDamage(8);
			damager->SetTag("PlayerDamager");
			m_scene->AddActor(std::move(damager));
			m_hasAttacked = true;
		}

		if (m_rendererComponent->IsAnimationDone())
		{
			m_state = State::Move;
			m_rendererComponent->Play("idle");
		}
	}
		break;
	case CharacterBase::State::Hit:
		m_state = State::Move;
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

	m_physicsComponent->SetVelocity(velocity);

	gl::Engine::Get().GetRenderer().SetCamera(m_physicsComponent->GetPosition());

	CharacterBase::Update(dt);
}

void PlayerController::OnCollision(gl::Actor* other)
{
	if (other->GetTag() == "EnemyDamager" && m_state != State::Death)
	{
		m_state = State::Hit;
		Damager* damager = dynamic_cast<Damager*>(other);
		if (damager) m_health -= damager->GetDamage();
		if (m_health <= 0.0f)
		{
			m_rendererComponent->Play("death");
			m_state = State::Death;
			auto game = dynamic_cast<SpriteGame*>(m_scene->GetGame());
			game->LifeLost();
		}

		other->SetDestroyed();
	}
}

void PlayerController::Read(const gl::json::value_t& value)
{
	CharacterBase::Read(value);
}
