#include "RenderableSDL.h"
#include "WindowSDL.h"
#include "Application.h"

#include <SDL.h>

void Hesketh::RenderableSDL::RetrieveTexture(char* filepath)
{
	m_texture = static_cast<SDL_Texture*>(Application::Instance().ResourceLoader()->GetResource("Texture", filepath));
}

Hesketh::RenderableSDL::RenderableSDL(char* filepath)
{
	RetrieveTexture(filepath);
}

Hesketh::RenderableSDL::~RenderableSDL()
{
}

void Hesketh::RenderableSDL::Render()
{
	float ptm = Application::Instance().Window()->GetPixelsToMetre();	// We convert from metres to pixels
	int screenHeight = Application::Instance().Window()->GetHeight();	// We need to subtract the y from the height, to flip the direction of the y axis

	SDL_Rect rect{ m_owner->GetTopLeftPosition()[0] * ptm, screenHeight - m_owner->GetTopLeftPosition()[1] * ptm, m_owner->GetWidth() * ptm, m_owner->GetHeight() * ptm };
	SDL_RenderCopyEx(static_cast<WindowSDL*>(Application::Instance().Window())->GetRenderer(), m_texture, NULL, &rect, m_owner->GetAngle(), NULL, SDL_FLIP_NONE);
}
