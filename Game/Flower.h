#pragma once
#include "Actor.h"

struct FlowerDesc : public gl::ActorDesc
{
	float decayRate = 0.0f;
};

class Flower : public gl::Actor
{
public:
	Flower() = default;
	Flower(const FlowerDesc& flowerDesc) :
		Actor{ flowerDesc },
		m_decayRate{ flowerDesc.decayRate }
	{
		m_lifespan = 10.0f;
	}
	Flower(const gl::Transform& transform) : Actor{ transform } {}
	Flower(const gl::Transform& transform, const gl::Model& model) : Actor{ transform, model } {}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

private:
	float m_decayRate = 1.0f;
	bool m_decaying = true;
	float m_pollination = 0.0f;
};