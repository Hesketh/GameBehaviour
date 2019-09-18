#pragma once
#include "Vector2.h"

namespace Hesketh
{
	class ConvexCollider;

	class CollisionData
	{
	private:
		bool m_collides;
		//Vector2 m_point;
		Vector2 m_normal;
		float m_penetration;
		ConvexCollider* m_object;
	public:
		CollisionData();
		CollisionData(/*const Vector2& collisionPoint,*/ const Vector2& collisionNormal, const float& penetration, ConvexCollider* object);
		~CollisionData();

		inline bool Collides() { return m_collides; };
		inline Vector2 Normal() { return m_normal; };
		inline float Penetration() { return m_penetration; };
		
		ConvexCollider* Object();
	};
}

