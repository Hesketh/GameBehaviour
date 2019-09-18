#include "WindowSDL.h"
#include "Messenger.h"

Hesketh::WindowSDL::WindowSDL()
{
	m_window	= nullptr;
	m_renderer	= nullptr;

	SDL_Init(SDL_INIT_VIDEO);

	m_window	= SDL_CreateWindow(m_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
	m_renderer	= SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}

Hesketh::WindowSDL::~WindowSDL() 
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

void Hesketh::WindowSDL::RenderClear()
{
	SDL_RenderClear(m_renderer);
}

void Hesketh::WindowSDL::RenderPresent()
{
	SDL_RenderPresent(m_renderer);
}