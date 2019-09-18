#pragma once
#include "Message.h"

namespace Hesketh
{
	class Receiver
	{
	public:
						Receiver()	{ /**/ };
		virtual			~Receiver() { /**/ };
		virtual void	HandleMessage(Message& message) = 0;
	};
}