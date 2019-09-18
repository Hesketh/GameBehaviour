#include "Entity.h"
#include "EntityComponent.h"

void Hesketh::Entity::DestroyComponents()
{
	for (auto const& x : m_components)
	{
		delete x.second;
	}
	m_components.clear();
}

Hesketh::Entity::Entity()
{
	m_components = std::map<std::string,EntityComponent*>();

	m_position = Vector2(0, 0);
	m_width = 0.0f;
	m_height = 0.0f;
	m_angle = 0.0f;
}

Hesketh::Entity::~Entity()
{
	DestroyComponents();
}

Hesketh::Vector2 Hesketh::Entity::GetPosition()
{
	return m_position;
}

void Hesketh::Entity::SetPosition(float x, float y)
{
	m_position = Vector2(x, y);
}

void Hesketh::Entity::SetPosition(Vector2 position)
{
	m_position = position;
}

Hesketh::Vector2 Hesketh::Entity::GetTopLeftPosition()
{
	return m_position + Vector2(-m_width / 2, m_height / 2);
}

Hesketh::Vector2 Hesketh::Entity::GetBottomLeftPosition()
{
	return m_position + Vector2(-m_width / 2, -m_height / 2);
}

void Hesketh::Entity::SetTopLeftPosition(Vector2 position)
{
	m_position = position + Vector2(m_width / 2, -m_height / 2);
}

float Hesketh::Entity::GetWidth()
{
	return m_width;
}

float Hesketh::Entity::GetHeight()
{
	return m_height;
}

void Hesketh::Entity::SetSize(float width, float height)
{
	m_width = width;
	m_height = height;
}

float Hesketh::Entity::GetAngle()
{
	return m_angle;
}

void Hesketh::Entity::SetAngle(float value)
{
	m_angle = value;

	if (m_angle > 359)
	{
		m_angle = m_angle - 360;
	}
	else if (m_angle < 0)
	{
		m_angle = 360 + m_angle;
	}
}

Hesketh::EntityComponent* Hesketh::Entity::GetComponent(std::string name)
{
	if (m_components.find(name) != m_components.end())
	{
		return m_components[name];
	}
	return nullptr;
}

void Hesketh::Entity::AddComponent(std::string name, EntityComponent* entity)
{
	m_components[name] = entity;
	entity->AssignOwner(this);
}

void Hesketh::Entity::Start()
{
	for (auto const &component : m_components)
	{
		component.second->Start();
	}
}

void Hesketh::Entity::Update()
{
	for (auto const &component : m_components)
	{
		component.second->Update();
	}
}

void Hesketh::Entity::FixedUpdate()
{
	for (auto const &component : m_components)
	{
		component.second->FixedUpdate();
	}
}