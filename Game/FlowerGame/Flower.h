#pragma once
#include "Framework/Actor.h"
#include "Renderer/Texture.h"

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
	Flower(const gl::Transform& transform, const std::shared_ptr<gl::Texture> sprite) : Actor{ transform, sprite } {}

	CLASS_PROTOTYPE(Flower)

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

	void Read(const gl::json::value_t& value) override;

private:
	float m_decayRate = 1.0f;
	bool m_decaying = true;
	float m_pollination = 0.0f;
};