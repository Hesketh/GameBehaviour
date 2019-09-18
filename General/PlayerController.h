#pragma once
#include "EntityComponent.h"
#include "CharacterController.h"
#include "RigidBody.h"

namespace Hesketh
{
	class PlayerController : public CharacterController
	{
	private:
	public:
		PlayerController();
		~PlayerController();

		void Start() override;
		void Update() override;
		void FixedUpdate() override;
	};

}
