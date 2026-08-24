#include "pch.h"
#include "EngineTime.h"

gl::Time::Time()
{
	Reset();
}

void gl::Time::Reset()
{
	m_startTicks = SDL_GetTicksNS();
	m_frameTicks = SDL_GetTicksNS();
	m_currentTicks = SDL_GetTicksNS();
}

void gl::Time::Tick()
{
	m_currentTicks = SDL_GetTicksNS();
	m_deltaTicks = m_currentTicks - m_frameTicks;
	m_frameTicks = m_currentTicks;
}
