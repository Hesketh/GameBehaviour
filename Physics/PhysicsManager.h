#pragma once
#include <vector>
#include "CollisionManager.h"
#include "RigidBody.h"
#include "Vector2.h"

namespace Hesketh
{
	class PhysicsManager
	{
	private:
		std::vector<RigidBody*>	m_bodies;
		CollisionManager		m_collision;
		Vector2					m_gravity;

		void ClearForces();
		void ApplyGravity();
	public:
		PhysicsManager();
		~PhysicsManager();

		void AddBody(RigidBody* body);
		void RemoveBodies();

		CollisionManager& GetCollisionManager();

		void Simulate(const float time);

		void SetGravity(const Vector2& accel);
	};
}
