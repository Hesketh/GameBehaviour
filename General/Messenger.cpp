#include "Messenger.h"

Hesketh::Messenger::Messenger()
{
	m_receivers = std::vector<Receiver*>();
	m_messages	= std::vector<Message>();
}

Hesketh::Messenger::~Messenger() {}

void Hesketh::Messenger::RegisterReceiver(Receiver* receiver)
{
	m_receivers.push_back(receiver);
}

void Hesketh::Messenger::QueueMessage(Message message)
{
	m_messages.push_back(message);
}

void Hesketh::Messenger::DispatchMessages()
{
	for (Message message : m_messages)
	{
		for (Receiver* receiver : m_receivers)
		{
			receiver->HandleMessage(message);
		}
	}
	m_messages.clear();
}

void Hesketh::Messenger::DispatchMessageImmediate(Message message)
{
	for (Receiver* receiver : m_receivers)
	{
		receiver->HandleMessage(message);
	}
}
