#pragma once
#include "Framework/Actor.h"
#include "Serialization/Json.h"

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
	Player(const gl::Transform& transform, const std::shared_ptr<gl::Texture> sprite) : Actor{ transform, sprite } {}

	CLASS_PROTOTYPE(Player)

	void Update(float dt) override;
	void Draw(const class gl::Renderer& renderer) const;

	void Read(const gl::json::value_t& value) override;

private:
	float m_speed = 100.0f;
};