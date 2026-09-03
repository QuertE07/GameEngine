#pragma once

#include "Framework/Actor.h"

class Damager : public gl::Actor {
public:
	CLASS_PROTOTYPE(Damager)

	void Read(const gl::json::value_t& value) override;

	const float& GetDamage() const { return m_damage; }
	void SetDamage(float damage) { m_damage = damage; }

protected:
	float m_damage{ 1.0f };
};