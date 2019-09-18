#pragma once
#include <deque>
#include "CharacterController.h"
#include "Vector2.h"
#include <vector>

namespace Hesketh
{
	class AIController : public CharacterController
	{
	private:
		std::deque<Vector2> m_path;
		std::vector<Entity*> m_targets;

		int m_pathCalcInterval = 270;
		int m_pathCurrInterval = 0;

		int m_stuckCount = 0;
	public:
		AIController();
		~AIController();

		void UpdatePath(Entity* target);
		void SetTargetEntity(std::vector<Entity*> targets);

		void Start() override;
		void Update() override;
		void FixedUpdate() override;
	};
}