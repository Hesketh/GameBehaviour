#include "Window.h"

Hesketh::Window::Window()
{
	Resize(1280, 720);
	SetTitle("Default");
	SetPixelsToMetre(64);
}

Hesketh::Window::Window(int width, int height)
{
	Resize(width, height);
	SetTitle("Default");
	SetPixelsToMetre(64);
}

Hesketh::Window::Window(int width, int height, char* title)
{
	Resize(width, height);
	SetTitle(title);
	SetPixelsToMetre(64);
}

void Hesketh::Window::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}

int Hesketh::Window::GetHeight()
{
	return m_height;
}

int Hesketh::Window::GetWidth()
{
	return m_width;
}

void Hesketh::Window::SetTitle(char* title)
{
	m_title = title;
}

void Hesketh::Window::SetPixelsToMetre(float pixels)
{
	m_pixelsToAMetre = pixels;
}

float Hesketh::Window::GetPixelsToMetre()
{
	return m_pixelsToAMetre;
}
