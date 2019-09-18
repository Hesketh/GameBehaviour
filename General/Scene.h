#pragma once
#include "Receiver.h"
#include "Messenger.h"
#include "Entity.h"
#include <vector>
#include <string>

// Physics Integration
#include "PhysicsManager.h"

namespace Hesketh
{
	class Scene
	{
	private:
		std::vector<Entity*>	m_entities;
		PhysicsManager			m_physics;

		void					ClearEntities();
	public:
		Scene();
		~Scene();

		std::vector<Entity*>	GetEntities();

		void Start();
		void Update();
		void FixedUpdate();
		void Render();

		void LoadScene(std::string filepath = "");
		void LoadDebugScene();

		std::vector<std::vector<int>> DiscretisedScene(std::vector<Entity*> ignore, double precision = 0.5);
	};
}