#include "FanController.h"
#include <vector>
#include "Application.h"
#include "Scene.h"
#include "RigidBody.h"

Hesketh::FanController::FanController()
{
}

Hesketh::FanController::~FanController()
{
}

void Hesketh::FanController::Start()
{
}

void Hesketh::FanController::Update()
{
}

void Hesketh::FanController::FixedUpdate()
{
	std::vector<Entity*> entities = Application::Instance().Scene()->GetEntities();

	for (Entity* entity : entities)
	{
		if (entity != m_owner)
		{
			RigidBody* rb = static_cast<RigidBody*>(entity->GetComponent("RigidBody"));
			if (rb)
			{
				if ((m_owner->GetPosition()[0] < entity->GetPosition()[0] && entity->GetPosition()[0] < m_owner->GetPosition()[0] + 8) &&
					(m_owner->GetPosition()[1] - 0.25 < entity->GetPosition()[1] && entity->GetPosition()[1] < m_owner->GetPosition()[1] + 0.25))
				{
					rb->AddForce(m_force);
				}
			}
		}
	}
}
