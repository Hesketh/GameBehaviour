#pragma once
#include "Vector2.h"
#include <map>
#include <string>

namespace Hesketh
{
	class EntityComponent;

	class Entity
	{
	protected:
		std::map<std::string, EntityComponent*>	m_components;

		Vector2	m_position;				// Centre Position
		float	m_width, m_height;		// Width and Height in metres
		float	m_angle;				// Angle rotated around its centre position

		void	DestroyComponents();
	public:
		Entity();
		virtual ~Entity();

		Vector2 GetPosition();
		void	SetPosition(float x, float y);
		void	SetPosition(Vector2 position);

		Vector2 GetTopLeftPosition();
		Vector2 GetBottomLeftPosition();
		void	SetTopLeftPosition(Vector2 position);

		float	GetWidth();
		float	GetHeight();
		void	SetSize(float width, float height);

		float	GetAngle();
		void	SetAngle(float value);

		EntityComponent* GetComponent(std::string name);
		void			 AddComponent(std::string name, EntityComponent* entity);

		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
	};
}
