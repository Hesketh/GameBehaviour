#include "CollisionData.h"
#include "ConvexCollider.h"

Hesketh::CollisionData::CollisionData()
{
	m_collides = false;
}

Hesketh::CollisionData::CollisionData(/*const Vector2 & collisionPoint,*/ const Vector2 & collisionNormal, const float & penetration, ConvexCollider* object)
{
	/*m_point = collisionPoint;*/
	m_normal = collisionNormal;
	m_penetration = penetration;
	m_collides = true;
	m_object = object;
}

Hesketh::CollisionData::~CollisionData()
{
}

Hesketh::ConvexCollider* Hesketh::CollisionData::Object()
{
	return m_object;
}
