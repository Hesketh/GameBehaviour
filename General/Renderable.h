#pragma once
#include "EntityComponent.h"

namespace Hesketh
{
	class Renderable : public EntityComponent
	{
	public:
		Renderable();
		~Renderable();

		virtual void	Render();
	};
}

