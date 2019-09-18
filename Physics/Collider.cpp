#include "Collider.h"
#include "RigidBody.h"

Hesketh::Collider::Collider()
{
}

Hesketh::Collider::~Collider()
{
}

Hesketh::AABB & Hesketh::Collider::GetBroad()
{
	return AABB(0 + m_owner->GetBottomLeftPosition()[0],
				0 + m_owner->GetBottomLeftPosition()[1],
				1 + m_owner->GetBottomLeftPosition()[0],
				1 + m_owner->GetBottomLeftPosition()[1]);
}

Hesketh::Vector2 Hesketh::Collider::GetCentrePosition()
{
	return m_owner->GetPosition();
}

void Hesketh::Collider::HandleCollision(CollisionData data)
{
	RigidBody* body = static_cast<RigidBody*>(GetComponent("RigidBody"));
	if (body)
	{
		body->ResolveCollision(data);
	}
}