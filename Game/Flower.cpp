#include "pch.h"
#include "Flower.h"
#include "Engine.h"
#include "FlowerGame.h"

void Flower::Update(float dt)
{
	if (m_decaying)
	{
		m_lifespan -= dt * m_decayRate;
		if (gl::RandomInt(10) == 0 && m_lifespan < 3.0f)
		{
			gl::Particle particle;
			particle.position = m_transform.position;
			particle.color = { 1.0f, 0.0f, 7.0f };
			particle.lifespan = gl::RandomFloat(0.5f, 1.5f);
			particle.velocity = { gl::RandomFloat(-50.0f, 50.0f), gl::RandomFloat(-50.0f, 50.0f) };

			gl::Engine::Get().GetPS().AddParticle(particle);
		}
	}
	else
	{
		m_pollination += dt;

		gl::Particle particle;
		particle.position = m_transform.position;
		particle.color = { 1.0f, 1.0f, 0.0f };
		particle.lifespan = gl::RandomFloat(0.5f, 1.5f);
		particle.velocity = { gl::RandomFloat(-50.0f, 50.0f), gl::RandomFloat(-50.0f, 50.0f) };

		gl::Engine::Get().GetPS().AddParticle(particle);
	}
	m_decaying = true;

	if (m_pollination > 3.0f)
	{
		m_destroyed = true;
		((FlowerGame*)m_scene->GetGame())->AddPoints(100);
		gl::Engine::Get().GetAudio().PlaySound("CompleteCharge");
	}
	else if (m_lifespan <= 0)
	{
		m_destroyed = true;
		((FlowerGame*)m_scene->GetGame())->LifeLost();
		gl::Engine::Get().GetAudio().PlaySound("FlowerWilt");

		for (int i = 0; i < 100; i++)
		{
			gl::Particle particle;
			particle.position = m_transform.position;
			particle.color = { 1.0f, 0.0f, 7.0f };
			particle.lifespan = gl::RandomFloat(0.5f, 1.5f);
			particle.velocity = { gl::RandomFloat(-200.0f, 200.0f), gl::RandomFloat(-200.0f, 200.0f) };

			gl::Engine::Get().GetPS().AddParticle(particle);
		}
	}
}

void Flower::OnCollision(Actor* other)
{
	if (other->GetTag() == "Player")
	{
		m_decaying = false;
	}
}
