#include "InputSDL.h"
#include "Application.h"
#include <SDL.h>

Hesketh::InputSDL::InputSDL()
{
}

Hesketh::InputSDL::~InputSDL()
{
}

void Hesketh::InputSDL::Process()
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
		case SDL_QUIT:
			Application::Instance().Kill();
			break;
		}
	}
}

bool Hesketh::InputSDL::GetKey(int key)
{
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	return keyboardState[key];
}

Hesketh::Vector2 Hesketh::InputSDL::GetMousePosition()
{
	int x, y = 0;
	SDL_GetMouseState(&x, &y);

	return Vector2(x, y);
}
