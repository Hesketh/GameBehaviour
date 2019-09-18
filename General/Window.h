#pragma once

namespace Hesketh
{
	class Window
	{
	protected:
		int		m_width;
		int		m_height;
		char*	m_title;

		float	m_pixelsToAMetre;
	public:
		Window();
		Window(int width, int height);
		Window(int width, int height, char* title);
		virtual ~Window() {};

		virtual void RenderClear()		= 0;
		virtual void RenderPresent()	= 0;

		void Resize(int width, int height);
		int GetHeight();
		int GetWidth();

		void SetTitle(char* title);

		void SetPixelsToMetre(float pixels);
		float GetPixelsToMetre();
	};
}