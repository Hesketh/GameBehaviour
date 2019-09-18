#pragma once
#include "EntityComponent.h"
#include "RigidBody.h"

namespace Hesketh
{
	class Pusher : public EntityComponent
	{
	private:
		RigidBody * m_body;

		Vector2 m_initial;
		float m_extendAmount;

		Entity* m_player;
		Entity* m_npc;
	public:
		Pusher(Entity* p, Entity* n);
		~Pusher();

		void Start() override;
		void Update() override;
		void FixedUpdate() override;
	};
}