#pragma once
#include "EntityComponent.h"

namespace Hesketh
{
	class FanController : public EntityComponent
	{
	private:
		Vector2 m_force = Vector2(5, 0);
	public:
		FanController();
		~FanController();

		void Start() override;
		void Update() override;
		void FixedUpdate() override;
	};
}