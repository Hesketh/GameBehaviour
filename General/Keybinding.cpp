#include "Keybinding.h"
#include "Application.h"

#include <SDL.h>

Hesketh::Keybinding::Keybinding()
{
	m_bindings = std::map<std::string, int>();

	m_bindings.insert(std::pair<std::string, int>("EXIT", 41));
}

Hesketh::Keybinding::~Keybinding()
{
}

bool Hesketh::Keybinding::GetBinding(std::string binding)
{
	if (m_bindings.find(binding) != m_bindings.end())
	{
		return Application::Instance().Input()->GetKey(m_bindings[binding]);
	}
	return false;
}

void Hesketh::Keybinding::SetBinding(std::string binding, int keycode)
{
	m_bindings.insert(std::pair<std::string, int>(binding, keycode));
}
