#pragma once
#include "Renderable.h"
#include <SDL.h>

namespace Hesketh
{
	class RenderableSDL : public Renderable
	{
	private:
		SDL_Texture*	m_texture;

		void RetrieveTexture(char* filepath);
	public:
		RenderableSDL(char* filepath);
		~RenderableSDL();

		void Render() override;
	};
}
