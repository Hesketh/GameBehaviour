#include "CoinController.h"
#include "Application.h"
#include "Scene.h"

Hesketh::CoinController::CoinController(Entity * player, Entity* npc)
{
	m_player = player;
	m_npc = npc;
}

Hesketh::CoinController::~CoinController()
{
}

void Hesketh::CoinController::Start()
{
	CoinsRemaining++;
}

void Hesketh::CoinController::Update()
{
}

#include <iostream>
void Hesketh::CoinController::FixedUpdate()
{
	if ((m_player->GetPosition() - m_owner->GetPosition()).Distance() < 1.0f)
	{
		m_owner->SetPosition(Vector2(10000, 10000));

		CoinsRemaining--;
		PlayerCoinsCollected++;

		if (CoinsRemaining < 1)
		{
			if (NPCCoinsCollected > PlayerCoinsCollected)
			{
				std::cout << "NPC ";
			}
			else
			{
				std::cout << "Player ";
			}

			std::cout << " wins!" << std::endl;
		}
	}
	else if ((m_npc->GetPosition() - m_owner->GetPosition()).Distance() < 1.0f)
	{
		m_owner->SetPosition(Vector2(10000, 10000));

		CoinsRemaining--;
		NPCCoinsCollected++;

		if (CoinsRemaining < 1)
		{
			if (NPCCoinsCollected > PlayerCoinsCollected)
			{
				std::cout << "NPC ";
			}
			else
			{
				std::cout << "Player ";
			}

			std::cout << "wins!" << std::endl;
		}
	}
}
