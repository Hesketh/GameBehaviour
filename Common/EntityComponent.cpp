#include "EntityComponent.h"
#include "Entity.h"

void Hesketh::EntityComponent::AssignOwner(Entity* owner)
{
	m_owner = owner;
}

Hesketh::EntityComponent* Hesketh::EntityComponent::GetComponent(std::string name)
{
	if(m_owner != nullptr)
	{
		return m_owner->GetComponent(name);
	}
	return nullptr;
}
