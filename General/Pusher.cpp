#include "Pusher.h"

Hesketh::Pusher::Pusher(Entity* p, Entity* n)
{
	m_player = p;
	m_npc = n;
}

Hesketh::Pusher::~Pusher()
{
}

void Hesketh::Pusher::Start()
{
	m_initial = m_owner->GetPosition();
	m_extendAmount = 1;
	m_body = static_cast<RigidBody*>(GetComponent("RigidBody"));
	m_body->IgnoreCollisionImpulse();
}

void Hesketh::Pusher::Update()
{
}

#include <iostream>
void Hesketh::Pusher::FixedUpdate()
{
	m_body->AddForce(Vector2(0, 9.81 * m_body->GetMass()));
	if (m_owner->GetPosition()[1] > m_initial[1] + m_extendAmount)
	{
		m_owner->SetPosition(Vector2(m_initial[0], m_initial[1] + m_extendAmount));
	}

	float minX = m_initial[0] - 1.5;
	float x = m_player->GetPosition()[0];
	float maxX = m_initial[0] + 1.5;

	if (minX < x && x < maxX)
	{
		if (m_body)
		{
			m_body->AddForce(Vector2(0, 300));
		}
	}
}