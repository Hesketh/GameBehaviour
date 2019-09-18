#pragma once
#include "Receiver.h"
#include "Message.h"
#include <vector>

namespace Hesketh
{
	class Messenger
	{
	private:
		std::vector<Receiver*>	m_receivers;
		std::vector<Message>	m_messages;

				Messenger();
		virtual ~Messenger();
	public:
		//Ownership is not taken with this pointer
		void RegisterReceiver(Receiver* receiver);
		void QueueMessage(Message message);
		void DispatchMessages();
		void DispatchMessageImmediate(Message message);
	};
}