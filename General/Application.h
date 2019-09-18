#pragma once
#include "Window.h"
#include "ResourceLoader.h"
#include "Scene.h"
#include "Keybinding.h"
#include "Input.h"

namespace Hesketh
{
	class Application
	{
	private:
		Window*				m_window;
		ResourceLoader*		m_loader;
		Scene*				m_scene;
		Input*				m_input;
		Keybinding*			m_keyBindings;

		bool				m_terminate;
		bool				m_pause;

		unsigned int		m_fpsTarget,
							m_upsTarget,		//updates per second
							m_nextRenderTime,
							m_nextUpdateTime,
							m_previousTime,
							m_previousFixedTime,
							m_fixedDeltaTime,
							m_deltaTime;
	protected:
		Application();
		Application(const Application&);
		Application& operator=(const Application&);
		~Application();
	public:
		static Application& Instance()
		{
			static Application instance;
			return instance;
		}

		//Ownership is not given away
		Window*	Window()
		{
			return m_window;
		};

		//Ownership is not given away
		Input* Input()
		{
			return m_input;
		};

		//Ownership is not given away
		Keybinding* KeyBinding()
		{
			return m_keyBindings;
		};

		//Ownership is not given away
		Scene* Scene()
		{
			return m_scene;
		};

		//Ownership is not given away
		ResourceLoader* ResourceLoader()
		{
			return m_loader;
		};

		float	GetFixedDeltaTime();
		float	GetDeltaTime();

		void	Run();
		void	Freeze();
		void	Kill();
	};
}

