#pragma once
#include "Window.h"
#include <SDL.h>

namespace Hesketh
{
	class WindowSDL : public Window
	{
	private:
		SDL_Window*		m_window;
		SDL_Renderer*	m_renderer;
	public:
		WindowSDL();
		~WindowSDL();

		void RenderClear() override;
		void RenderPresent() override;

		SDL_Renderer*	GetRenderer()
		{
			return m_renderer;
		}
	};
}