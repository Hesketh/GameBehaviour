#pragma once
#include "ResourceLoader.h"
#include "Receiver.h"
#include <SDL.h>

namespace Hesketh
{
	class ResourceLoaderSDL : public ResourceLoader
	{
	private:
		ResourceContainer<SDL_Texture>	m_textures;
		SDL_Renderer*					m_renderer;

		void LoadTexture(std::string filepath);
	public:
		ResourceLoaderSDL();
		~ResourceLoaderSDL();

		void	LoadResource(std::string type, std::string filepath) override;
		void*	GetResource(std::string type, std::string filepath)	 override;
	};
}

