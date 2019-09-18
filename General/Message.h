#pragma once
#include "MessageType.h"

class Receiver;	//Forward declaration

namespace Hesketh
{
	struct Message
	{
		MessageType	type;
		void*		data;
	};
}