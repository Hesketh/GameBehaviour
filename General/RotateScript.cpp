#include "RotateScript.h"

Hesketh::RotateScript::RotateScript()
{
}

Hesketh::RotateScript::~RotateScript()
{
}

void Hesketh::RotateScript::Start()
{
	m_body = static_cast<RigidBody*>(GetComponent("RigidBody"));
	m_body->IgnoreCollisionImpulse();
}

void Hesketh::RotateScript::Update()
{
}

void Hesketh::RotateScript::FixedUpdate()
{
	m_body->AddForce(Vector2(0, 9.81) * m_body->GetMass());
	m_body->SetAngularVelocity(10);
}
