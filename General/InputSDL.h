#pragma once
#include "Input.h"
#include "Vector2.h"

namespace Hesketh
{
	class InputSDL : public Input
	{
	public:
		InputSDL();
		~InputSDL();

		void Process()			override;
		bool GetKey(int key)	override;
		Vector2 GetMousePosition() override;
	};

}
