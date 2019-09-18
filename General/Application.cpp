#include "Application.h"
#include "WindowSDL.h"
#include "ResourceLoaderSDL.h"
#include "InputSDL.h"
#include "Utility.h"

Hesketh::Application::Application()
{
	m_window	= new WindowSDL();
	m_loader	= new ResourceLoaderSDL();
	m_scene		= new Hesketh::Scene();
	m_input		= new InputSDL();
	m_keyBindings = new Keybinding();

	m_terminate = false;
	m_pause = false;

	m_fpsTarget = 60;
	m_upsTarget = 120;
	m_nextRenderTime	= Utility::GetTime();
	m_nextUpdateTime	= Utility::GetTime();
	m_previousTime		= Utility::GetTime();
	m_fixedDeltaTime	= 0;
	m_deltaTime			= 0;
}

Hesketh::Application::~Application()
{
	delete m_keyBindings;
	delete m_input;
	delete m_scene;
	delete m_loader;
	delete m_window;
}

float Hesketh::Application::GetFixedDeltaTime()
{
	return ((float)m_fixedDeltaTime) / 1000;
}

float Hesketh::Application::GetDeltaTime()
{
	return ((float)m_deltaTime) / 1000;
}

void Hesketh::Application::Run()
{
	m_scene->LoadScene();	// Load the hardcoded scene for testing

	m_scene->Start();

	while (!m_terminate)
	{
		unsigned int time = Utility::GetTime();
		m_deltaTime = time - m_previousTime;	// Time since last update
		m_fixedDeltaTime = time - m_previousFixedTime;	// Time since last fixed update

		if (!m_pause)
		{
			m_input->Process();
			m_scene->Update();
		}

		//Fixed Update - Limited by target Updates Per Second
		if (time >= m_nextUpdateTime && !m_pause)
		{
			m_previousFixedTime = time;
			m_scene->FixedUpdate();
			m_nextUpdateTime += 1000 / m_upsTarget;
		}

		//Render - Limited by target Frames Per Second
		if (time >= m_nextRenderTime && !m_pause)
		{
			m_window->RenderClear();
			m_scene->Render();
			m_window->RenderPresent();

			m_nextRenderTime += 1000 / m_fpsTarget;
		}

		m_previousTime = time;
	}
}

void Hesketh::Application::Freeze()
{
	m_pause = true;
}

void Hesketh::Application::Kill()
{
	m_terminate = true;
}

Hesketh::Application::Application(const Application &) { /* Operation Disabled */ }

Hesketh::Application& Hesketh::Application::operator=(const Application &) { /* Operation Disabled */ return *this; }

