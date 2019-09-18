#include "PhysicsManager.h"

void Hesketh::PhysicsManager::ClearForces()
{
	for (RigidBody* body : m_bodies)
	{
		body->ClearForces();
	}
}

void Hesketh::PhysicsManager::ApplyGravity()
{
	for (RigidBody* body : m_bodies)
	{
		body->AddForce(m_gravity * body->GetMass());
	}
}

Hesketh::PhysicsManager::PhysicsManager()
{
	m_bodies = std::vector<RigidBody*>();
	m_collision = CollisionManager();
	m_gravity = Vector2(0, 0);
}

Hesketh::PhysicsManager::~PhysicsManager()
{
}

void Hesketh::PhysicsManager::AddBody(RigidBody* body)
{
	m_bodies.push_back(body);
}

void Hesketh::PhysicsManager::RemoveBodies()
{
	m_bodies.clear();
}

Hesketh::CollisionManager& Hesketh::PhysicsManager::GetCollisionManager()
{
	return m_collision;
}

void Hesketh::PhysicsManager::Simulate(const float time)
{
	// Perform Collision Detection / Handling
	m_collision.HandleCollisions();

	// Calculate Velocities, etc.
	for (RigidBody* body : m_bodies)
	{
		body->Solve(time);
	}

	ClearForces();
	ApplyGravity();
}

void Hesketh::PhysicsManager::SetGravity(const Vector2& accel)
{
	m_gravity = accel;
}
