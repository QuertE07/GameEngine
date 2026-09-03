#pragma once
#include "Framework/Actor.h"

class CharacterBase : public gl::Actor
{
public:
	enum class State
	{
		Move,
		Attack,
		Hit,
		Death
	};

	void Read(const gl::json::value_t& value) override;

protected:
	State m_state = State::Move;
	float m_stateTimer = 0.0f;
	float m_health = 10.0f;

	bool m_hasAttacked = false;
};