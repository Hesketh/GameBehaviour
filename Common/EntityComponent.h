#pragma once
#include <string>
#include "Entity.h"

namespace Hesketh
{
	class EntityComponent
	{
	protected:
		Entity* m_owner;
	public:
		EntityComponent() { /**/ };
		virtual ~EntityComponent() { /**/ };

		virtual void Start() { /**/ };
		virtual void Update() { /**/ };
		virtual void FixedUpdate() { /**/ };

		// Assigns the owner of this component, so the component can request information of other entities
		void AssignOwner(Entity* owner);

		// Gets the Component from the parent
		EntityComponent* GetComponent(std::string name);
	};
}