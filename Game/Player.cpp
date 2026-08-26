#include "Player.h"
#include "Engine.h"
#include "Components/PhysicsComponent.h"

#include <SDL3/SDL.h>

FACTORY_REGISTER(Player)

void Player::Update(float dt)
{
    gl::Vector2 inputDir{ (float)gl::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT) - gl::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LEFT),
                          (float)gl::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_DOWN) - gl::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_UP)};

    float thrust = inputDir.y * m_speed;
    float rotate = inputDir.x * 400;

    auto physicsComponent = GetComponent<gl::PhysicsComponent>();
    if (physicsComponent)
    {
        gl::Vector2 forward{ 0, 1 };
        gl::Vector2 force = forward.Rotate(m_transform.rotation * gl::DegToRad) * thrust;
        physicsComponent->ApplyForce(force);

        physicsComponent->ApplyTorque(rotate);

        physicsComponent->SetPosition({ gl::Wrap(0.0f, 1920.0f, physicsComponent->GetPosition().x), gl::Wrap(0.0f, 1080.0f, physicsComponent->GetPosition().y)});
    }

    double inputMagnitude = std::sqrt(std::pow(inputDir.x, 2) + std::pow(inputDir.y, 2));
    inputDir /= gl::Max((float)inputMagnitude, 1.0f);

    //Actor::SetVelocity(Actor::GetVelocity() + inputDir * m_speed);

    Actor::Update(dt);

    //Actor::m_transform.rotation = Actor::GetVelocity().Angle() * gl::RadToDeg + 90;

    //gl::Particle particle;
    //particle.position = m_transform.position;
    //particle.color = { 1.0f, 1.0f, 1.0f };
    //particle.lifespan = gl::RandomFloat(0.5f, 1.5f);
    //particle.velocity = { gl::RandomFloat(-200.0f, 200.0f), gl::RandomFloat(-200.0f, 200.0f) };

    //gl::Engine::Get().GetPS().AddParticle(particle);
}

void Player::Draw(const class gl::Renderer& renderer) const
{
	Actor::Draw(renderer);
}

void Player::Read(const gl::json::value_t& value)
{
    Actor::Read(value);

    
    JSON_READ_NAME(value, "speed", m_speed);
}