#pragma once
#include "Vector2.h"

namespace Hesketh
{
	class Input
	{
	public:
				Input() { /**/ }
		virtual	~Input() { /**/ }

		virtual void Process()				= 0;
		virtual bool GetKey(int key)		= 0;
		virtual Vector2 GetMousePosition()	= 0;
	};
}