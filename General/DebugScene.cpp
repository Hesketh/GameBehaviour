#pragma once
#include "Scene.h"

// General
#include "Application.h"
#include "Entity.h"
#include "FloatingPlatformController.h"
#include "RenderableSDL.h"
#include "Pusher.h"
#include "RotateScript.h"
#include "CoinController.h"
#include "FanController.h"

// Physics
#include "RigidBody.h"

// AI
#include "AIController.h"
#include "PlayerController.h"

// Requirements
// Atleast Two Tiers of Platforms
// Atleast Four Moving Obstacles (Boxes, Moving Platform, Coin)
// Conisder Environmental Forces such as wind and surface friction that will affect movement (Fan)

void Hesketh::Scene::LoadDebugScene()
{
	//Create the Background
	{
		Entity* background = new Entity();
		background->SetSize(20, 11.25);
		background->SetTopLeftPosition(Vector2(0, Application::Instance().Window()->GetHeight() / Application::Instance().Window()->GetPixelsToMetre()));
		background->AddComponent("Renderable", new RenderableSDL("Assets/background.bmp"));
		m_entities.push_back(background);
	}

	//Create the blocks around the screen
	{
		//Floor
		{
			//	Renderable
			Entity* block = new Entity();
			block->SetSize(19, 0.5);
			block->SetTopLeftPosition(Vector2(0.5, 0.5));
			block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
			m_entities.push_back(block);

			// Physics
			ConvexCollider* blockCollider = new ConvexCollider();

			blockCollider->AddPoint(Vector2(0, 0));
			blockCollider->AddPoint(Vector2(19, 0));
			blockCollider->AddPoint(Vector2(19, 0.5));
			blockCollider->AddPoint(Vector2(0, 0.5));

			block->AddComponent("Collider", blockCollider);
			m_physics.GetCollisionManager().AddCollider(blockCollider);

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		}

		//Roof
		{
			//	Renderable
			Entity* block = new Entity();
			block->SetSize(19, 0.5);
			block->SetTopLeftPosition(Vector2(0.5, 11.5));
			block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
			m_entities.push_back(block);

			// Physics
			ConvexCollider* blockCollider = new ConvexCollider();

			blockCollider->AddPoint(Vector2(0, 0));
			blockCollider->AddPoint(Vector2(19, 0));
			blockCollider->AddPoint(Vector2(19, 0.5));
			blockCollider->AddPoint(Vector2(0, 0.5));

			block->AddComponent("Collider", blockCollider);
			m_physics.GetCollisionManager().AddCollider(blockCollider);

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		}

		// Left Wall
		{
			//	Renderable
			Entity* block = new Entity();
			block->SetSize(0.5, 11.5);
			block->SetTopLeftPosition(Vector2(0, 11.5));
			block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
			m_entities.push_back(block);

			// Physics
			ConvexCollider* blockCollider = new ConvexCollider();

			blockCollider->AddPoint(Vector2(0, 0));
			blockCollider->AddPoint(Vector2(0.5, 0));
			blockCollider->AddPoint(Vector2(0.5, 11.5));
			blockCollider->AddPoint(Vector2(0, 11.5));

			block->AddComponent("Collider", blockCollider);
			m_physics.GetCollisionManager().AddCollider(blockCollider);

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		}

		// Right Wall
		{
			//	Renderable
			Entity* block = new Entity();
			block->SetSize(0.5, 11.5);
			block->SetTopLeftPosition(Vector2(19.5, 11.5));
			block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
			m_entities.push_back(block);

			// Physics
			ConvexCollider* blockCollider = new ConvexCollider();

			blockCollider->AddPoint(Vector2(0, 0));
			blockCollider->AddPoint(Vector2(0.5, 0));
			blockCollider->AddPoint(Vector2(0.5, 11.5));
			blockCollider->AddPoint(Vector2(0, 11.5));

			block->AddComponent("Collider", blockCollider);
			m_physics.GetCollisionManager().AddCollider(blockCollider);

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		}

	}

	//Create some block high up
	{
		//Left
		{
			//	Renderable
			Entity* block = new Entity();
			block->SetSize(5, 0.5);
			block->SetTopLeftPosition(Vector2(2.5, 8.5));
			block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
			m_entities.push_back(block);

			// Physics
			ConvexCollider* blockCollider = new ConvexCollider();

			blockCollider->AddPoint(Vector2(0, 0));
			blockCollider->AddPoint(Vector2(5, 0));
			blockCollider->AddPoint(Vector2(5, 0.5));
			blockCollider->AddPoint(Vector2(0, 0.5));

			block->AddComponent("Collider", blockCollider);
			m_physics.GetCollisionManager().AddCollider(blockCollider);

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		}

		//Right
		{
			//	Renderable
			Entity* block = new Entity();
			block->SetSize(5, 0.5);
			block->SetTopLeftPosition(Vector2(12.5, 8.5));
			block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
			m_entities.push_back(block);

			// Physics
			ConvexCollider* blockCollider = new ConvexCollider();

			blockCollider->AddPoint(Vector2(0, 0));
			blockCollider->AddPoint(Vector2(5, 0));
			blockCollider->AddPoint(Vector2(5, 0.5));
			blockCollider->AddPoint(Vector2(0, 0.5));

			block->AddComponent("Collider", blockCollider);
			m_physics.GetCollisionManager().AddCollider(blockCollider);

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		}

		//Center
		{
			//	Renderable
			Entity* block = new Entity();
			block->SetSize(6, 0.5);
			block->SetTopLeftPosition(Vector2(5.5, 6.5));
			block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
			m_entities.push_back(block);

			// Physics
			ConvexCollider* blockCollider = new ConvexCollider();

			blockCollider->AddPoint(Vector2(0, 0));
			blockCollider->AddPoint(Vector2(6, 0));
			blockCollider->AddPoint(Vector2(6, 0.5));
			blockCollider->AddPoint(Vector2(0, 0.5));

			block->AddComponent("Collider", blockCollider);
			m_physics.GetCollisionManager().AddCollider(blockCollider);

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		}
	}

	//Create the Player
	Entity* player = new Entity();
	{
		player->SetSize(0.5, 1);
		player->SetTopLeftPosition(Vector2(18.5, 5));
		player->AddComponent("Renderable", new RenderableSDL("Assets/player.bmp"));
		m_entities.push_back(player);

		ConvexCollider* playerCollider = new ConvexCollider();

		playerCollider->AddPoint(Vector2(0, 0));
		playerCollider->AddPoint(Vector2(0.5, 0));
		playerCollider->AddPoint(Vector2(0.5, 1));
		playerCollider->AddPoint(Vector2(0, 1));

		player->AddComponent("RigidBody", new RigidBody(RigidBodyType::Dynamic, 1));
		m_physics.AddBody(static_cast<RigidBody*>(player->GetComponent("RigidBody")));
		static_cast<RigidBody*>(player->GetComponent("RigidBody"))->SetLinearDamping(Vector2(1.0f, 0.0f));

		player->AddComponent("Collider", playerCollider);
		m_physics.GetCollisionManager().AddCollider(playerCollider);

		player->AddComponent("PlayerController", new PlayerController());
	}

	//Create the AI
	Entity* npc = new Entity();
	{
		npc->SetSize(0.5, 1);
		npc->SetPosition(Vector2(1.5, 5));
		npc->AddComponent("Renderable", new RenderableSDL("Assets/npc.bmp"));
		m_entities.push_back(npc);

		ConvexCollider* npcCollider = new ConvexCollider();

		npcCollider->AddPoint(Vector2(0, 0));
		npcCollider->AddPoint(Vector2(0.5, 0));
		npcCollider->AddPoint(Vector2(0.5, 1));
		npcCollider->AddPoint(Vector2(0, 1));

		npc->AddComponent("RigidBody", new RigidBody(RigidBodyType::Dynamic, 1));
		m_physics.AddBody(static_cast<RigidBody*>(npc->GetComponent("RigidBody")));
		static_cast<RigidBody*>(npc->GetComponent("RigidBody"))->SetLinearDamping(0.3f);

		npc->AddComponent("Collider", npcCollider);
		m_physics.GetCollisionManager().AddCollider(npcCollider);

		npc->AddComponent("AIController", new AIController());
	}

	//Pushable Crates
	{
		{
			//	Renderable
			Entity* block = new Entity();
			block->SetSize(1, 1);
			block->SetTopLeftPosition(Vector2(10, 10));
			block->AddComponent("Renderable", new RenderableSDL("Assets/crate.bmp"));
			m_entities.push_back(block);

			// Physics
			block->AddComponent("Collider", new ConvexCollider());
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(1, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(1, 1));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 1));
			m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(block->GetComponent("Collider")));

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Dynamic, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
			static_cast<RigidBody*>(block->GetComponent("RigidBody"))->SetLinearDamping(0.9f);
		}

		{
			//	Renderable
			Entity* block = new Entity();
			block->SetSize(1, 1);
			block->SetTopLeftPosition(Vector2(9, 3));
			block->AddComponent("Renderable", new RenderableSDL("Assets/crate.bmp"));
			m_entities.push_back(block);

			// Physics
			block->AddComponent("Collider", new ConvexCollider());
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(1, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(1, 1));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 1));
			m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(block->GetComponent("Collider")));

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Dynamic, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
			static_cast<RigidBody*>(block->GetComponent("RigidBody"))->SetLinearDamping(0.9f);
		}

		{
			//	Renderable
			Entity* block = new Entity();
			block->SetSize(1, 1);
			block->SetTopLeftPosition(Vector2(7.2, 4.5));
			block->AddComponent("Renderable", new RenderableSDL("Assets/crate.bmp"));
			m_entities.push_back(block);

			// Physics
			block->AddComponent("Collider", new ConvexCollider());
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(1, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(1, 1));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 1));
			m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(block->GetComponent("Collider")));

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Dynamic, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
			static_cast<RigidBody*>(block->GetComponent("RigidBody"))->SetLinearDamping(0.9f);
		}
	}

	//Moving Floating Platform
	{
		//	Renderable
		Entity* block = new Entity();
		block->SetSize(3, 0.5);
		block->SetTopLeftPosition(Vector2(10.5, 4));
		block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
		m_entities.push_back(block);

		// Physics
		block->AddComponent("Collider", new ConvexCollider());
		static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
		static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(3, 0));
		static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(3, 0.5));
		static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 0.5));
		m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(block->GetComponent("Collider")));

		block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Dynamic, 1));
		m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		static_cast<RigidBody*>(block->GetComponent("RigidBody"))->SetLinearDamping(0.9f);

		block->AddComponent("FPController", new FloatingPlatformController());
	}

	/*/Pusher thing
	{
		//	Renderable
		Entity* block = new Entity();
		block->SetSize(5, 1);
		block->SetTopLeftPosition(Vector2(12, 2));
		block->AddComponent("Renderable", new RenderableSDL("Assets/crate.bmp"));
		m_entities.push_back(block);

		// Physics
		block->AddComponent("Collider", new ConvexCollider());
		static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
		static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(5, 0));
		static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(5, 1));
		static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 1));
		m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(block->GetComponent("Collider")));

		block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Dynamic, 1));
		m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		static_cast<RigidBody*>(block->GetComponent("RigidBody"))->SetLinearDamping(0.9f);

		block->AddComponent("PController", new Pusher(player, npc));
	}
	//*/

	// Rotated static
	{
		//Left
		for (int i = 0; i < 10; i++)
		{
			//	Renderable
			Entity* block = new Entity();
			block->SetSize(0.5, 0.5);
			block->SetTopLeftPosition(Vector2(0 + i * 0.25, 11 - i * 0.25));
			block->SetAngle(45);
			block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
			m_entities.push_back(block);

			// Physics
			ConvexCollider* blockCollider = new ConvexCollider();

			blockCollider->AddPoint(Vector2(0, 0));
			blockCollider->AddPoint(Vector2(0.5, 0));
			blockCollider->AddPoint(Vector2(0.5, 0.5));
			blockCollider->AddPoint(Vector2(0, 0.5));

			block->AddComponent("Collider", blockCollider);
			m_physics.GetCollisionManager().AddCollider(blockCollider);

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		}

		//Right
		for (int i = 0; i < 10; i++)
		{
			//	Renderable
			Entity* block = new Entity();
			block->SetSize(0.5, 0.5);
			block->SetTopLeftPosition(Vector2(19.5 - i * 0.25, 11 - i * 0.25));
			block->SetAngle(45);
			block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
			m_entities.push_back(block);

			// Physics
			ConvexCollider* blockCollider = new ConvexCollider();

			blockCollider->AddPoint(Vector2(0, 0));
			blockCollider->AddPoint(Vector2(0.5, 0));
			blockCollider->AddPoint(Vector2(0.5, 0.5));
			blockCollider->AddPoint(Vector2(0, 0.5));

			block->AddComponent("Collider", blockCollider);
			m_physics.GetCollisionManager().AddCollider(blockCollider);

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		}
	}

	// Upper Platforms
	{
		{
			Entity* block = new Entity();
			block->SetSize(4, 4);
			block->SetTopLeftPosition(Vector2(2, 4.5));
			block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
			m_entities.push_back(block);

			// Physics
			block->AddComponent("Collider", new ConvexCollider());
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(4, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(4, 4));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 4));
			m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(block->GetComponent("Collider")));

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		}

		{
			Entity* block = new Entity();
			block->SetSize(1.5, 2);
			block->SetTopLeftPosition(Vector2(0.5, 2.5));
			block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
			m_entities.push_back(block);

			// Physics
			block->AddComponent("Collider", new ConvexCollider());
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(2, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(2, 2));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 2));
			m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(block->GetComponent("Collider")));

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		}

		{
			Entity* block = new Entity();
			block->SetSize(4, 4);
			block->SetTopLeftPosition(Vector2(14, 4.5));
			block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
			m_entities.push_back(block);

			// Physics
			block->AddComponent("Collider", new ConvexCollider());
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(4, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(4, 4));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 4));
			m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(block->GetComponent("Collider")));

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		}

		{
			Entity* block = new Entity();
			block->SetSize(1.5, 2);
			block->SetTopLeftPosition(Vector2(18, 2.5));
			block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
			m_entities.push_back(block);

			// Physics
			block->AddComponent("Collider", new ConvexCollider());
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(2, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(2, 2));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 2));
			m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(block->GetComponent("Collider")));

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		}

		{
			Entity* block = new Entity();
			block->SetSize(1, 2);
			block->SetTopLeftPosition(Vector2(13, 2.5));
			block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
			m_entities.push_back(block);

			// Physics
			block->AddComponent("Collider", new ConvexCollider());
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(1, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(1, 2));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 2));
			m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(block->GetComponent("Collider")));

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		}

		{
			Entity* block = new Entity();
			block->SetSize(1, 2);
			block->SetTopLeftPosition(Vector2(6, 2.5));
			block->AddComponent("Renderable", new RenderableSDL("Assets/block.bmp"));
			m_entities.push_back(block);

			// Physics
			block->AddComponent("Collider", new ConvexCollider());
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(1, 0));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(1, 2));
			static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 2));
			m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(block->GetComponent("Collider")));

			block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
			m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));
		}
	}

	//*/ Giant Fan
	{
		//	Renderable
		Entity* block = new Entity();
		block->SetSize(1, 1);
		block->SetTopLeftPosition(Vector2(5, 3.5));
		block->AddComponent("Renderable", new RenderableSDL("Assets/fan.bmp"));
		m_entities.push_back(block);

		// Physics
		block->AddComponent("Collider", new ConvexCollider());
		static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
		static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(1, 0));
		static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(1, 1));
		static_cast<ConvexCollider*>(block->GetComponent("Collider"))->AddPoint(Vector2(0, 1));
		m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(block->GetComponent("Collider")));

		block->AddComponent("RigidBody", new RigidBody(RigidBodyType::Static, 1));
		m_physics.AddBody(static_cast<RigidBody*>(block->GetComponent("RigidBody")));

		block->AddComponent("FController", new FanController());
	} 
	//*/

	// Coins
	{
		auto coins = std::vector<Entity*>();
		{
			//	Renderable
			Entity* coin = new Entity();
			coin->SetSize(0.5, 1);
			coin->SetTopLeftPosition(Vector2(4, 4));
			coin->AddComponent("Renderable", new RenderableSDL("Assets/coin.bmp"));
			m_entities.push_back(coin);

			// Physics
			coin->AddComponent("Collider", new ConvexCollider());
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0.5, 0));
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0.5, 1));
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0, 1));
			m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(coin->GetComponent("Collider")));

			coin->AddComponent("RigidBody", new RigidBody(RigidBodyType::Dynamic, 2));
			m_physics.AddBody(static_cast<RigidBody*>(coin->GetComponent("RigidBody")));

			coin->AddComponent("CoinController", new CoinController(player, npc));
			coins.push_back(coin);
		}

		{
			//	Renderable
			Entity* coin = new Entity();
			coin->SetSize(0.5, 1);
			coin->SetTopLeftPosition(Vector2(12, 9));
			coin->AddComponent("Renderable", new RenderableSDL("Assets/coin.bmp"));
			m_entities.push_back(coin);

			// Physics
			coin->AddComponent("Collider", new ConvexCollider());
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0.5, 0));
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0.5, 1));
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0, 1));
			m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(coin->GetComponent("Collider")));

			coin->AddComponent("RigidBody", new RigidBody(RigidBodyType::Dynamic, 2));
			m_physics.AddBody(static_cast<RigidBody*>(coin->GetComponent("RigidBody")));

			coin->AddComponent("CoinController", new CoinController(player, npc));
			coins.push_back(coin);
		}

		{
			//	Renderable
			Entity* coin = new Entity();
			coin->SetSize(0.5, 1);
			coin->SetTopLeftPosition(Vector2(4, 9));
			coin->AddComponent("Renderable", new RenderableSDL("Assets/coin.bmp"));
			m_entities.push_back(coin);

			// Physics
			coin->AddComponent("Collider", new ConvexCollider());
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0.5, 0));
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0.5, 1));
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0, 1));
			m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(coin->GetComponent("Collider")));

			coin->AddComponent("RigidBody", new RigidBody(RigidBodyType::Dynamic, 2));
			m_physics.AddBody(static_cast<RigidBody*>(coin->GetComponent("RigidBody")));

			coin->AddComponent("CoinController", new CoinController(player, npc));
			coins.push_back(coin);
		}

		{
			//	Renderable
			Entity* coin = new Entity();
			coin->SetSize(0.5, 1);
			coin->SetTopLeftPosition(Vector2(2, 10));
			coin->AddComponent("Renderable", new RenderableSDL("Assets/coin.bmp"));
			m_entities.push_back(coin);

			// Physics
			coin->AddComponent("Collider", new ConvexCollider());
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0.5, 0));
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0.5, 1));
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0, 1));
			m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(coin->GetComponent("Collider")));

			coin->AddComponent("RigidBody", new RigidBody(RigidBodyType::Dynamic, 2));
			m_physics.AddBody(static_cast<RigidBody*>(coin->GetComponent("RigidBody")));

			coin->AddComponent("CoinController", new CoinController(player, npc));
			coins.push_back(coin);
		}

		{
			//	Renderable
			Entity* coin = new Entity();
			coin->SetSize(0.5, 1);
			coin->SetTopLeftPosition(Vector2(18, 10));
			coin->AddComponent("Renderable", new RenderableSDL("Assets/coin.bmp"));
			m_entities.push_back(coin);

			// Physics
			coin->AddComponent("Collider", new ConvexCollider());
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0, 0));
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0.5, 0));
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0.5, 1));
			static_cast<ConvexCollider*>(coin->GetComponent("Collider"))->AddPoint(Vector2(0, 1));
			m_physics.GetCollisionManager().AddCollider(static_cast<ConvexCollider*>(coin->GetComponent("Collider")));

			coin->AddComponent("RigidBody", new RigidBody(RigidBodyType::Dynamic, 2));
			m_physics.AddBody(static_cast<RigidBody*>(coin->GetComponent("RigidBody")));

			coin->AddComponent("CoinController", new CoinController(player, npc));
			coins.push_back(coin);
		}

		static_cast<AIController*>(npc->GetComponent("AIController"))->SetTargetEntity(coins);
	}
}