#pragma once
#include "EntityComponent.h"
#include "RigidBody.h"

namespace Hesketh
{
	class FloatingPlatformController : public EntityComponent
	{
	private:
		RigidBody * m_body;

		int m_updatesTillReversal = 0;
		int m_direction = 1;
	public:
		FloatingPlatformController();
		~FloatingPlatformController();

		void Start() override;
		void Update() override;
		void FixedUpdate() override;
	};
}