#include "pch.h"
#include "Engine.h"
#include "framework.h"

namespace gl
{
	bool Engine::Initialize()
	{
		m_renderer.Initialize("Game", 1920, 1080);
		m_input.Initialize();
		m_particleSystem.Initialize(5000);
		m_audio.Initialize();
		m_physics.Initialize();

		return true;
	}

	void Engine::Shutdown()
	{
		m_physics.Shutdown();
		m_audio.Shutdown();
		m_particleSystem.Shutdown();
		m_input.Shutdown();
		m_renderer.Shutdown();
	}

	void Engine::Update()
	{
		m_time.Tick();
		m_input.Update();
		m_particleSystem.Update(m_time.GetDeltaTime());
		m_audio.Update();
		m_physics.Update(m_time.GetDeltaTime());
	}
}