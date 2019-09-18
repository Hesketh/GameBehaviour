#include "RigidBody.h"
#include <limits>
#include <iostream>

Hesketh::RigidBody::RigidBody()
{
	m_type = RigidBodyType::Dynamic;
	SetMass(1);

	m_centreOfMass = Vector2(0, 0);

	m_velocity = Vector2(0, 0);
	m_bonusVelocity = Vector2(0, 0);
	m_angularVelocity = 0;

	m_linearDamping = Vector2(0,0);
	m_angularDamping = 0;

	m_forces = Vector2(0, 0);
	m_impulses = Vector2(0, 0);
	m_torque = 0.0f;
	m_inertia = 1.0f;	// TODO: Figure out how to calculate this
}

Hesketh::RigidBody::RigidBody(RigidBodyType type, float mass)
{
	m_type = type;
	SetMass(mass);

	m_centreOfMass = Vector2(0, 0);

	m_velocity = Vector2(0, 0);
	m_bonusVelocity = Vector2(0, 0);
	m_angularVelocity = 0;

	m_linearDamping = Vector2(0,0);
	m_angularDamping = 0.0f;

	m_forces = Vector2(0, 0);
	m_torque = 0.0f;
	m_inertia = 1.0f;	// TODO: Figure out how to calculate this
	m_ignoreCollisionImpulse = false;
}

Hesketh::RigidBody::~RigidBody()
{
}

void Hesketh::RigidBody::SetCentre(const Vector2 & centre)
{
	m_centreOfMass = centre;
}

Hesketh::Vector2 Hesketh::RigidBody::GetCentre() const
{
	return m_centreOfMass;
}

void Hesketh::RigidBody::SetMass(const float& mass)
{
	if (m_type == RigidBodyType::Static || m_type == RigidBodyType::Kinematic)
	{
		m_mass = 0;
	}
	else
	{
		m_mass = mass;
	}
}

float Hesketh::RigidBody::GetMass() const
{
	if (m_type == RigidBodyType::Static)
	{
		return std::numeric_limits<float>().infinity();
	}
	return m_mass;
}

void Hesketh::RigidBody::AddBonusVelocity(const Vector2 bonus)
{
	// Used for character control, helps avoid just infinitely accelerating which results in floaty character movement
	m_bonusVelocity = m_bonusVelocity + bonus;
}

// BUG: Gravity constantly applys a downward velocity so the object keeps getting faster, the impulse applied opposite to it doesnt change the velocity. So we have a problem
void Hesketh::RigidBody::Solve(const float time)
{
	if (m_type == RigidBodyType::Dynamic)
	{
		// Apply Forces and Torque to calculate velocities
		m_velocity = m_velocity + (m_impulses * (1 / GetMass()));
		m_velocity = m_velocity + ((m_forces * (1 / GetMass()) * time));
		m_angularVelocity = m_angularVelocity + ((m_torque * (1 / m_inertia) * time));

		// Apply damping to the velocities
		m_velocity[0] = m_velocity[0] * 1.0f / (1.0f + time * m_linearDamping[0]);
		m_velocity[1] = m_velocity[1] * 1.0f / (1.0f + time * m_linearDamping[1]);
		m_angularVelocity = m_angularVelocity * 1.0f / (1.0f + time * m_angularDamping);
	}

	// Update the position of the body / entity
	if (m_type != RigidBodyType::Static)
	{
		m_owner->SetPosition(m_owner->GetPosition() + (m_velocity + m_bonusVelocity) * time);
		m_owner->SetAngle(m_owner->GetAngle() + (m_angularVelocity)* time);
	}
}

void Hesketh::RigidBody::AddImpulse(const Vector2& impulse)
{
	if (m_type == RigidBodyType::Dynamic)
	{
		m_impulses = m_impulses + impulse;
	}
}

void Hesketh::RigidBody::AddForce(const Vector2& force)
{
	if (m_type == RigidBodyType::Dynamic)
	{
		m_forces = m_forces + force;
	}
}

void Hesketh::RigidBody::AddForce(const Vector2 & force, const Vector2 & point)
{
	if (m_type == RigidBodyType::Dynamic)
	{
		m_forces = m_forces + force;

		Vector2 pointToCentre = point - m_centreOfMass;
		m_torque = m_torque + pointToCentre.Cross(force);
	}
}

void Hesketh::RigidBody::AddTorque(const float & torque)
{
	if (m_type == RigidBodyType::Dynamic)
	{
		m_torque = m_torque + torque;
	}
}

Hesketh::RigidBodyType Hesketh::RigidBody::GetType() const
{
	return m_type;
}

void Hesketh::RigidBody::AddVelocity(const Vector2 acc)
{
	m_velocity = m_velocity + acc;
}

void Hesketh::RigidBody::SetLinearVelocity(const Vector2 & velocity)
{
	m_velocity = velocity;
}

Hesketh::Vector2 Hesketh::RigidBody::GetLinearVelocity() const
{
	return m_velocity;
}

void Hesketh::RigidBody::SetAngularVelocity(const float & velocity)
{
	m_angularVelocity = velocity;
}

float Hesketh::RigidBody::GetAngularVelocity() const
{
	return m_angularVelocity;
}

void Hesketh::RigidBody::SetLinearDamping(const float damping)
{
	m_linearDamping = Vector2(damping, damping);
}

void Hesketh::RigidBody::SetLinearDamping(const Vector2 damping)
{
	m_linearDamping = damping;
}

void Hesketh::RigidBody::SetAngularDamping(const float damping)
{
	m_angularDamping = damping;
}

#include "ConvexCollider.h"
void Hesketh::RigidBody::ResolveCollision(CollisionData& data)
{
	if (m_type != RigidBodyType::Dynamic)
	{
		return;
	}

	// Collision Resolution
	EntityComponent* other = data.Object();
	if (RigidBody* rb = static_cast<RigidBody*>(other->GetComponent("RigidBody")))
	{
		if (m_type == RigidBodyType::Dynamic && !m_ignoreCollisionImpulse)
		{
			// Moves the object out of the collision
			m_owner->SetPosition(m_owner->GetPosition() + data.Normal() * (data.Penetration() + FLT_EPSILON));

			// Applied an equal but opposite force
			Vector2 opVel = rb->GetLinearVelocity() * data.Normal(); // Potentially add  rb->m_bonusVelocity to here but not the bonus from this object
			float opMass = rb->GetMass();

			float restitution = 0.0f;
			float impulse = -(1 + restitution)*((m_velocity + opVel).Dot(data.Normal())) / ((1 / GetMass()) + (1 / opMass));

			AddImpulse(data.Normal() * impulse);
		}
	}
	else
	{
		// This is not a collision between two rigidbodies, so dont do physics on the collision
	}
}

void Hesketh::RigidBody::IgnoreCollisionImpulse(bool value)
{
	m_ignoreCollisionImpulse = value;
}

void Hesketh::RigidBody::ClearForces()
{
	m_forces = Vector2(0, 0);
	m_impulses = Vector2(0, 0);
	m_bonusVelocity = Vector2(0, 0);
}
