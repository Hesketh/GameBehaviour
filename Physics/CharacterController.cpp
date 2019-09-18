#include "CharacterController.h"
#include "RigidBody.h"

void Hesketh::CharacterController::Jump()
{
	m_jump = true;
}

void Hesketh::CharacterController::MoveLeft()
{
	m_movingLeft = true;
}

void Hesketh::CharacterController::MoveRight()
{
	m_movingRight = true;
}

Hesketh::CharacterController::CharacterController()
{
	m_body = nullptr;
}

Hesketh::CharacterController::~CharacterController()
{
}

void Hesketh::CharacterController::Start()
{
	m_movingLeft = m_movingRight = false;
	m_canJump = true;
	m_jump = false;

	m_body = static_cast<RigidBody*>(GetComponent("RigidBody"));
}

void Hesketh::CharacterController::Update()
{
}

void Hesketh::CharacterController::FixedUpdate()
{
	const float speed = 3.0f;
	const float jumpPower = 7.5f;

	m_canJump = 0.2f > m_body->GetLinearVelocity()[1] && m_body->GetLinearVelocity()[1] > -0.2f;

	if (m_movingLeft)
	{
		m_body->AddBonusVelocity(Vector2(-speed, 0));
	}
	if (m_movingRight)
	{
		m_body->AddBonusVelocity(Vector2(speed, 0));
	}

	if (m_jump && m_canJump)
	{
		m_body->AddImpulse(Vector2(0, jumpPower));
	}

	m_movingLeft = m_movingRight = m_jump = false;
}
