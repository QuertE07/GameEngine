#pragma once

#include "CharacterBase.h"

namespace gl
{
	class PhysicsComponent;
	class SpriteAnimatorRendererComponent;
}

class FlyingEnemyController : public CharacterBase
{
public:
	CLASS_PROTOTYPE(FlyingEnemyController)

		void Start() override;
	void Update(float dt) override;

	void OnCollision(gl::Actor* other) override;

	void Read(const gl::json::value_t& value) override;

protected:
	gl::PhysicsComponent* m_physicsComponent = nullptr;
	gl::SpriteAnimatorRendererComponent* m_rendererComponent = nullptr;
};