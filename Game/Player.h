#pragma once
#include "Actor.h"

struct PlayerDesc : public gl::ActorDesc
{
	float speed = 0.0f;
};

class Player : public gl::Actor
{
public:
	Player() = default;
	Player(const PlayerDesc& playerDesc) :
		Actor{ playerDesc },
		m_speed{ playerDesc.speed }
	{}
	Player(const gl::Transform& transform) : Actor{ transform } {}
	Player(const gl::Transform& transform, const gl::Model& model) : Actor{ transform, model } {}

	void Update(float dt) override;
	void Draw(const class gl::Renderer& renderer) const;

private:
	float m_speed = 100.0f;
};