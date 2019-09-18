#pragma once
#include <map>
#include <string>

namespace Hesketh
{
	class Keybinding
	{
	private:
		std::map<std::string, int> m_bindings;
	public:
		Keybinding();
		~Keybinding();

		bool GetBinding(std::string binding);
		void SetBinding(std::string binding, int keycode);
	};
}
