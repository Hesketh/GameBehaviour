#pragma once
#include "EntityComponent.h"

namespace Hesketh
{
	class RigidBody;

	class CharacterController : public EntityComponent
	{
	private:
		bool m_movingRight, m_movingLeft;
		bool m_canJump, m_jump;
	protected:
		void Jump();
		void MoveLeft();
		void MoveRight();
		RigidBody* m_body;
	public:
		CharacterController();
		~CharacterController();

		void Start() override;
		void Update() override;
		void FixedUpdate() override;
	};
}