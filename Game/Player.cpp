#include "Player.h"
#include "Engine.h"

#include <SDL3/SDL.h>

FACTORY_REGISTER(Player)

void Player::Update(float dt)
{
    gl::Vector2 inputDir{ (float)gl::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT) - gl::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LEFT),
                          (float)gl::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_DOWN) - gl::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_UP)};

    double inputMagnitude = std::sqrt(std::pow(inputDir.x, 2) + std::pow(inputDir.y, 2));
    inputDir /= gl::Max((float)inputMagnitude, 1.0f);

    Actor::SetVelocity(Actor::GetVelocity() + inputDir * m_speed);

    Actor::Update(dt);

    Actor::m_transform.rotation = Actor::GetVelocity().Angle() * gl::RadToDeg + 90;

    //gl::Particle particle;
    //particle.position = m_transform.position;
    //particle.color = { 1.0f, 1.0f, 1.0f };
    //particle.lifespan = gl::RandomFloat(0.5f, 1.5f);
    //particle.velocity = { gl::RandomFloat(-200.0f, 200.0f), gl::RandomFloat(-200.0f, 200.0f) };

    //gl::Engine::Get().GetPS().AddParticle(particle);

    m_transform.position.x = gl::Wrap(0.0f, 1920.0f, m_transform.position.x);
    m_transform.position.y = gl::Wrap(0.0f, 1080.0f, m_transform.position.y);
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