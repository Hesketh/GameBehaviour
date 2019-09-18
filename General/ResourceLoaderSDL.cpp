#include "ResourceLoaderSDL.h"
#include "MessageType.h"
#include "Messenger.h"
#include "Application.h"
#include "WindowSDL.h"

Hesketh::ResourceLoaderSDL::ResourceLoaderSDL()
{
	//We cannot get this here because Resource Loaders are made when the application is. 
	//m_renderer = static_cast<WindowSDL*>(Application::Instance().GetWindow())->GetRenderer();
	m_renderer = nullptr;
	m_textures = ResourceContainer<SDL_Texture>();
}

Hesketh::ResourceLoaderSDL::~ResourceLoaderSDL() { /**/ }

void Hesketh::ResourceLoaderSDL::LoadTexture(std::string filepath)
{
	if (m_renderer == nullptr)
	{
		m_renderer = static_cast<WindowSDL*>(Application::Instance().Window())->GetRenderer();
	}

	if (!m_textures.GetResource(filepath) && m_renderer != nullptr)
	{
		SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 255));
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		SDL_FreeSurface(surface);

		m_textures.AddResource(filepath, texture);
	}
}

void Hesketh::ResourceLoaderSDL::LoadResource(std::string type, std::string filepath)
{
	if (type == "Texture")
	{
		LoadTexture(filepath);
	}
}

void* Hesketh::ResourceLoaderSDL::GetResource(std::string type, std::string filepath)
{
	LoadResource(type, filepath);

	if (type == "Texture")
	{
		return m_textures.GetResource(filepath);
	}
	return NULL;
}