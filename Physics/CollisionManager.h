#pragma once
#include <vector>
#include "CollisionData.h"
#include "ConvexCollider.h"

namespace Hesketh
{
	class Collider;

	class CollisionManager
	{
	private:
		std::vector<Collider*> m_colliders;
		std::vector<std::pair<float, Collider*>> m_prune;

		std::vector<std::pair<Collider*, Collider*>> BroadPhase();
		Projection CalculateProjection(ConvexCollider& polygon, Vector2& axis);
	public:
		CollisionManager();
		~CollisionManager();

		CollisionData Collides(ConvexCollider* polygonA, ConvexCollider* polygonB);

		void AddCollider(Collider* collider);
		void HandleCollisions();
	};
}