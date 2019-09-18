#pragma once
#include "AABB.h"
#include "EntityComponent.h"
#include "CollisionData.h"
#include "Vector2.h"

namespace Hesketh
{
	class Collider : public EntityComponent
	{
	public:
		Collider();
		~Collider();

		virtual AABB& GetBroad();

		Vector2 GetCentrePosition();

		void HandleCollision(CollisionData data);
	};
}
