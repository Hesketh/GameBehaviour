#pragma once
#include "EntityComponent.h"

namespace Hesketh
{
	class FollowMouse : public EntityComponent
	{
	private:
	public:
		FollowMouse() { /**/ };
		~FollowMouse() { /**/ };

		void Update() override;
		void FixedUpdate() override;
	};
}