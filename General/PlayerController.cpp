#include "PlayerController.h"
#include "Application.h"
#include "Keybinding.h"
#include <cmath>

Hesketh::PlayerController::PlayerController()
{
}

Hesketh::PlayerController::~PlayerController()
{
}

void Hesketh::PlayerController::Start()
{
	//https://www.libsdl.org/tmp/SDL/include/SDL_scancode.h
	Application::Instance().KeyBinding()->SetBinding("Player_Jump", 26);
	Application::Instance().KeyBinding()->SetBinding("Player_Right", 7);
	Application::Instance().KeyBinding()->SetBinding("Player_Left", 4);

	CharacterController::Start();
}

void Hesketh::PlayerController::Update()
{

}

void Hesketh::PlayerController::FixedUpdate()
{	
	if (Application::Instance().KeyBinding()->GetBinding("Player_Right"))
	{
		MoveRight();
	}

	if (Application::Instance().KeyBinding()->GetBinding("Player_Left"))
	{
		MoveLeft();
	}

	if (Application::Instance().KeyBinding()->GetBinding("Player_Jump"))
	{
		Jump();
	}

	CharacterController::FixedUpdate();
}
