#pragma once

#include "File.h"
#include "MathUtils.h"
#include "Random.h"
#include "Transform.h"
#include "Vector2.h"
#include "Vector3.h"
#include "AnimatedModel.h"
#include "Text.h"
#include "Json.h"
#include "StringUtils.h"

#include "Renderer.h"
#include "Input.h"
#include "EngineTime.h"
#include "ParticleSystem.h"
#include "ResourceManager.h"
#include "Audio.h"
#include "Texture.h"
#include "Physics/Physics.h"

#include "Factory.h"

#include "Actor.h"
#include "Scene.h"
#include "Game.h"

#include <iostream>
#include <vector>


namespace gl
{
	class Engine
	{
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();
		
		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }
		ParticleSystem& GetPS() { return m_particleSystem; }
		Audio& GetAudio() { return m_audio; }
		Physics& GetPhysics() { return m_physics; }

	private:
		Engine() = default;

		Input m_input;
		Renderer m_renderer;

		Time m_time;

		ParticleSystem m_particleSystem;
		Audio m_audio;

		Physics m_physics;
	};
}