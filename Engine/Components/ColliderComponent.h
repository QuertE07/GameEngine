#pragma once
#include "Framework/Component.h"

namespace gl
{
	class ColliderComponent : public Component
	{
	public:
		virtual bool CheckCollision(const ColliderComponent& other) = 0;
	};
}