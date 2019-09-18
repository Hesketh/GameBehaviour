#include "FloatingPlatformController.h"

Hesketh::FloatingPlatformController::FloatingPlatformController()
{
}

Hesketh::FloatingPlatformController::~FloatingPlatformController()
{
}

void Hesketh::FloatingPlatformController::Start()
{
	m_body = static_cast<RigidBody*>(GetComponent("RigidBody"));
	m_body->IgnoreCollisionImpulse();
}

void Hesketh::FloatingPlatformController::Update()
{
}

void Hesketh::FloatingPlatformController::FixedUpdate()
{
	if (m_body)
	{
		m_updatesTillReversal--;

		if(m_updatesTillReversal < 0)
		{
			m_updatesTillReversal = 500;
			m_direction = m_direction * -1;
		}

		m_body->AddForce(Vector2(0, 9.81 * m_body->GetMass()));
		m_body->AddBonusVelocity(Vector2(m_direction, 0));
	}
}
