#pragma once
#include "EntityComponent.h"
#include "RigidBody.h"

namespace Hesketh
{
	class RotateScript : public EntityComponent
	{
	private:
		RigidBody * m_body;
	public:
		RotateScript();
		~RotateScript();

		void Start() override;
		void Update() override;
		void FixedUpdate() override;
	};
}