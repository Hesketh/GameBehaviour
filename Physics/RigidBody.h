#pragma once
#include "EntityComponent.h"
#include "CollisionData.h"
#include "Vector2.h"

namespace Hesketh
{
	enum class RigidBodyType
	{
		Static = 0,
		Kinematic = 1,
		Dynamic = 2
	};

	class RigidBody : public EntityComponent
	{
	private:
		RigidBodyType m_type;
		float	m_mass;

		Vector2 m_velocity;
		Vector2 m_bonusVelocity;
		float	m_angularVelocity;

		Vector2	m_linearDamping;
		float	m_angularDamping;

		Vector2 m_centreOfMass;

		Vector2 m_forces;
		Vector2 m_impulses;
		float	m_torque;
		float	m_inertia;

		bool	m_ignoreCollisionImpulse;
	public:
		RigidBody();
		RigidBody(RigidBodyType type, float mass);
		~RigidBody();

		void SetCentre(const Vector2& centre);
		Vector2 GetCentre() const;

		void SetMass(const float& mass);
		float GetMass() const;

		void AddBonusVelocity(const Vector2 bonus);

		void Solve(const float time);

		void AddImpulse(const Vector2& force);

		void AddForce(const Vector2& force);
		void AddForce(const Vector2& force, const Vector2& point);
		void AddTorque(const float& torque);

		RigidBodyType GetType() const;

		void AddVelocity(const Vector2 acc);

		void SetLinearVelocity(const Vector2& velocity);
		Vector2 GetLinearVelocity() const;

		void SetAngularVelocity(const float& velocity);
		float GetAngularVelocity() const;

		void SetLinearDamping(const float damping);
		void SetLinearDamping(const Vector2 damping);
		void SetAngularDamping(const float damping);

		void ResolveCollision(CollisionData& data);
		void IgnoreCollisionImpulse(bool value = true);

		void ClearForces();
	};
}