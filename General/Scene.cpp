#include "Scene.h"
#include <cmath>
#include <iostream>
#include "Application.h"
#include "EntityComponent.h"
#include "Renderable.h"

void Hesketh::Scene::ClearEntities()
{
	for (Entity* entity : m_entities)
	{
		delete entity;
		entity = nullptr;
	}
	m_entities.clear();
}

Hesketh::Scene::Scene()
{
	m_entities = std::vector<Entity*>();
	m_physics = PhysicsManager();
}

Hesketh::Scene::~Scene()
{
	ClearEntities();
}

std::vector<Hesketh::Entity*> Hesketh::Scene::GetEntities()
{
	return m_entities;
}

void Hesketh::Scene::Start()
{
	m_physics.SetGravity(Vector2(0, -9.81));

	for (Entity* entity : m_entities)
	{
		entity->Start();
	}
}

void Hesketh::Scene::Update()
{
	for (Entity* entity : m_entities)
	{
		entity->Update();
	}
}

void Hesketh::Scene::FixedUpdate()
{
	m_physics.Simulate(Application::Instance().GetFixedDeltaTime());

	for (Entity* entity : m_entities)
	{
		entity->FixedUpdate();
	}
}

void Hesketh::Scene::Render()
{
	for (Entity* entity : m_entities)
	{
		EntityComponent* component = entity->GetComponent("Renderable");

		if (component != nullptr)
		{
			(static_cast<Renderable*>(component))->Render();
		}
	}
}

void Hesketh::Scene::LoadScene(std::string filepath)
{
	if (filepath == "")
	{
		LoadDebugScene();
	}
}

std::vector<std::vector<int>>  Hesketh::Scene::DiscretisedScene(std::vector<Entity*> ignore, double precision)
{
	int valuesPerSingle = 1 / precision;
	double width = Application::Instance().Window()->GetWidth() / Application::Instance().Window()->GetPixelsToMetre();
	double height = Application::Instance().Window()->GetHeight() / Application::Instance().Window()->GetPixelsToMetre();
	
	std::vector<std::vector<int>> scene = std::vector<std::vector<int>>(width * valuesPerSingle, std::vector<int>(height * valuesPerSingle));

	// We initially say the entire map is traversable
	for (double x = 0; x < width; x+= precision)
	{
		for (double y = 0; y < height; y += precision)
		{
			try
			{
				scene.at(x * valuesPerSingle).at(y * valuesPerSingle) = 0;
			}
			catch (const std::out_of_range& oor) {
				// Do nothing if OOB, dont want to stop execution of the game
			}
		}
	}

	// We iterate through the entities on the scene, if they have a collider we need to say that the position of that entity is untraverable
	for (auto entity : m_entities)
	{
		bool skip = false;
		for (auto e : ignore)
		{
			if (e == entity)
			{
				skip = true;
				break;
			}
		}
		if (skip)
		{
			continue;
		}

		if (entity->GetComponent("Collider"))
		{
			double minAllignedX = std::floor(entity->GetBottomLeftPosition()[0] / precision) * precision;
			double maxAllignedX = std::ceil((entity->GetBottomLeftPosition()[0] + entity->GetWidth()) / precision) * precision;

			double minAllignedY = std::floor(entity->GetBottomLeftPosition()[1] / precision) * precision;
			double maxAllignedY = std::ceil((entity->GetBottomLeftPosition()[1] + entity->GetHeight()) / precision) * precision;

			for (double x = minAllignedX; x <= maxAllignedX; x += precision)
			{
				for (double y = minAllignedY; y <= maxAllignedY; y += precision)
				{
					try
					{
						scene.at(x * valuesPerSingle).at(y * valuesPerSingle) = 1;
					}
					catch (const std::out_of_range& oor) {
						// Do nothing if OOB, dont want to stop execution of the game
					}
				}
			}
		}
	}

	/*
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	for (double y = height - 1; y >= 0; y -= precision)
	{
		for (double x = 0; x < width; x += precision)
		{
			std::cout << scene[x * valuesPerSingle][y * valuesPerSingle];
		}
		std::cout << std::endl;
	}
	//*/

	return scene;
}

